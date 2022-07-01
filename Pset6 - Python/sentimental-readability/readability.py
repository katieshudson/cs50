from cs50 import get_string


def main():

    # TO DO
    # 1) input text from user (get_string -- "Text:  ")

    # 2) analyze text with formula to determine grade level
    # - count number of total letters total
    # - count number of sentences
    # - count number of words
    # - Calculate "L" = number of letters per 100 words (letters / words * 100 = L)
    # - Calculate "S" = number of sentences per 100 words (sentences / 14 words * 100 = S)

    # // 3) output grade level of text (ie. Grade 3)

    # ACCEPT USER TEXT INPUT
    user_text = get_string("Text: ")

    # Variables for calculating index score
    num_letters = calculate_letters(user_text)
    num_words = calculate_words(user_text)
    num_sentences = calculate_sentences(user_text)
    grade_level_index = calculate_index(num_letters, num_words, num_sentences)

    # OUTPUT GRADE LEVEL
    if grade_level_index < 1:
        print("Before Grade 1")
    elif grade_level_index >= 16:
        print("Grade 16+")
    else:
        print(f"Grade: ", grade_level_index)


def calculate_letters(user_text):

    # count num letters (characters) from user_text input - subtract spaces
    count_letters = len(user_text) - user_text.count(" ") - user_text.count(".") - user_text.count("?") - user_text.count("!") - user_text.count("'") - user_text.count(",")
    
    return count_letters


def calculate_words(user_text):

    # count num of words from user_text input
    word_count = len(user_text.split())

    return word_count


def calculate_sentences(user_text):

    sentence_count = 0
    for char in user_text:
        # 46 = "."  | 33 = "!" | 63 = "?"
        if ord(char) == 46 or ord(char) == 33 or ord(char) == 63:
            sentence_count += 1

    return sentence_count


def calculate_index(letters, words, sentences):

    grade_level = 0
    letters_per_hundred = 0
    sentences_per_hundred = 0

    # Calculate L - letters / words * 100 = L
    letters_per_hundred = (letters / words) * 100

    # Calculate S - sentences / words * 100 = S
    sentences_per_hundred = (sentences / words) * 100

    # Calculate index grade_level with Coleman-Liau index formula
    # (0.0588 * L) - (0.296 * S) - 15.8
    grade_level = round((0.0588 * letters_per_hundred) - (0.296 * sentences_per_hundred) - 15.8)

    return grade_level


if __name__ == "__main__":
    main()