import os
import datetime

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
from functools import reduce

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    user_id = session["user_id"]

    stocks_portfolio = db.execute(
        "SELECT symbol, company_name, SUM(num_shares) AS num_shares, price FROM transactions WHERE user_id = ? GROUP BY symbol ORDER BY symbol", user_id)
    cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)  # returns list of dictionaries
    cash_balance = usd(cash[0]["cash"])  # returns actual value of cash

    total_value = 0
    for stock in stocks_portfolio:
        total_value = total_value + (stock["num_shares"] * stock["price"])

    # new_total_value = reduce(lambda x,y: x+ (y["num_shares"]*y["price"]),stocks_portfolio, 0)   alternative method

    return render_template("index.html", stocks_portfolio=stocks_portfolio, cash=cash_balance, total_value=total_value)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == "POST":
        user_id = session["user_id"]
        buy_symbol = request.form.get("symbol")
        num_shares = request.form.get("shares")  # have to force this to be an int
        stock_quote = lookup(buy_symbol)
        transaction_type = "BUY"
        date = datetime.datetime.now()

        if buy_symbol == "":  # if symbol field is left blank
            return apology("must enter a stock symbol")
        if stock_quote == None:   # if stock symbol does not exist / match stock database
            return apology("sorry, stock symbol does not exist")

        try:
            if int(num_shares) < 0:
                return apology("sorry, you must enter a valid number of shares")
        except:
            return apology("sorry, you must buy whole shares")

        stock_current_price = stock_quote["price"]
        company_name = stock_quote["name"]

        cash_balance = db.execute("SELECT cash FROM users WHERE id = ?", user_id)  # returns a dictionary key/pair value
        user_cash = cash_balance[0]["cash"]  # gets actual cash value from user
        cash_needed = float(stock_current_price) * int(num_shares)

        if user_cash < cash_needed:  # not enough cash in account
            apology("sorry, you do not have enough cash to make this purchase")

        new_cash_balance = user_cash - cash_needed

        # Update cash value of user in user database
        db.execute("UPDATE users SET cash = ? WHERE id = ?", new_cash_balance, user_id)

        # Record transaction of user in transactions database
        db.execute("INSERT INTO transactions (user_id, symbol, num_shares, price, date, transaction_type, company_name) VALUES (?,?,?,?,?,?,?)",
        user_id, buy_symbol, num_shares, stock_quote["price"], date, transaction_type, company_name)

        flash('Shares purchased!')  # banner message

        return redirect("/")  # direct to index page

    else:  # GET method
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    user_id = session["user_id"]

    transaction_history = db.execute("SELECT * FROM transactions WHERE user_id = ?", user_id)

    return render_template("history.html", transaction_history=transaction_history)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # CHECK FOR ERRORS
        symbol = request.form.get("symbol")
        stock = lookup(symbol)

        # Ensure Symbol was submitted
        if not symbol:
            return apology("must provide symbol", 400)

        if stock:
            return render_template("display-quote.html", name=stock["name"], symbol=stock["symbol"], price=stock["price"])

        else:  # UNSUCCESSFUL - stock symbol doesn't exist
            return apology("Stock symbol doesn't exist", 400)

    # GET METHOD - display form
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

    # CHECK FOR ERRORS
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        if not request.form.get("password"):
            return apology("must provide password", 400)

        # Ensure passwords match
        if not (request.form.get("password") == request.form.get("confirmation")):
            return apology("passwords must match", 400)

    # *** ADD USER TO DATABASE ****
        # Generate hash of password
        pwHash = generate_password_hash(request.form.get("password"))
        username = request.form.get("username")

        # Insert new user information into database
        try:
            new_user = db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, pwHash)  # username has to be unique

        except:   # was the username actually inserted into the database
            return apology("username could not be created", 400)

        # Log user in - associate the id of user  to the session of the user
        session["user_id"] = new_user

        # registration success message
        flash("Yay! You have successfully registered for an account")

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    user_id = session["user_id"]

    # uses HAVING SUM SQL query to ensure that there are positive number of shares
    stocks_portfolio = db.execute(
        "SELECT symbol FROM transactions WHERE user_id = ? GROUP BY symbol HAVING SUM(num_shares) > 0", user_id)

    if request.method == "POST":

        sell_symbol = request.form.get("symbol")
        num_shares_sold = int(request.form.get("shares"))  # have to force to be an int - # of shares you want to sell
        stock_quote = lookup(sell_symbol)
        transaction_type = "SELL"
        date = datetime.datetime.now()
        num_shares_db = db.execute(
            "SELECT num_shares FROM transactions WHERE user_id = ? AND symbol = ? GROUP BY symbol", user_id, sell_symbol)
        num_shares_avail = num_shares_db[0]["num_shares"]  # gets actual number from the list

        # CHECK FOR ERRORS
        if not sell_symbol:  # if no stock symbol selected from drop down menu
            return apology("must select stock symbol", 400)

        if num_shares_sold < 1:  # if user chooses 0 or negative number
            return apology("sorry, you must enter a valid number of shares")

        # CHECK IF USER OWNS ENOUGH** STOCK
        if num_shares_sold > num_shares_avail:
            return apology("sorry you don't own that many shares. try again")

        # RECORD TRANSACTION
        stock_current_price = stock_quote["price"]
        company_name = stock_quote["name"]

        cash_balance = db.execute("SELECT cash FROM users WHERE id = ?", user_id)  # returns a dictionary key/pair value
        user_cash = cash_balance[0]["cash"]  # gets actual cash value from user
        transaction_value = stock_current_price * num_shares_sold

        new_cash_balance = user_cash + transaction_value

        # Update cash value of user in user database
        db.execute("UPDATE users SET cash = ? WHERE id = ?", new_cash_balance, user_id)

        # Record transaction of user in transactions database
        db.execute("INSERT INTO transactions (user_id, symbol, num_shares, price, date, transaction_type, company_name) VALUES (?, ?, ?, ?, ?, ?, ?)",
            user_id, sell_symbol, (-1)*num_shares_sold, stock_quote["price"], date, transaction_type, company_name)

        flash('Shares sold!')  # banner message

        return redirect("/")

    else:
        return render_template("/sell.html", stocks_portfolio=stocks_portfolio)


@app.route("/cash", methods=["GET", "POST"])
@login_required
def cash():
    """Add more cash"""

    user_id = session["user_id"]

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # CHECK FOR ERRORS
        cash_to_add = int(request.form.get("cash"))

        # Ensure Symbol was submitted
        if cash_to_add == "":
            return apology("must provide amount")

        if cash_to_add < 1:
            return apology("must add $1 or more to account")

        # query current cash balance
        current_cash_balance = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
        user_cash = current_cash_balance[0]["cash"]  # gets actual cash value from user

        new_cash_balance = cash_to_add + user_cash

        # add cash to users database
        db.execute("UPDATE users SET cash = ? WHERE id = ?", new_cash_balance, user_id)

        flash("Cash added to account")  # banner message

        return redirect("/")

    # GET METHOD - display form
    else:
        return render_template("cash.html")
