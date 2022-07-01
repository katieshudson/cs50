/* -- write a SQL query to list the names of all people who have directed a movie that received a rating of at least 9.0.
 directors
 FOREIGN KEY(movie_id) REFERENCES movies(id),
 FOREIGN KEY(person_id) REFERENCES people(id)

 movies
 id --> primary key

 people
 id --> primary key

 people.id = directors.person_id
 people --> directors

 ratings.movie_id = directors.movie_id
 ratings --> directors

 -- movies that has ratings of 9
 -- directors of those movies
 -- names of directors of those movies of rating of 9

 -- what limits the set the most? --- do this first

 */

SELECT DISTINCT
    people.name

FROM
    ratings
INNER JOIN directors ON (ratings.movie_id = directors.movie_id)
INNER JOIN people ON (directors.person_id = people.id)

WHERE
    ratings.rating >= 9
ORDER BY
    people.name DESC;