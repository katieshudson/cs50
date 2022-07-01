-- find all of the movies that have Chadwick in it
-- list out all movies with chadwick and their rating
-- order list of movies with him that are highest rated in desc
-- limit search to top 5
-- then only use title of movie for your list

-- movies id -- stars movie id person id people id


SELECT
    movies.title

FROM
    movies
    INNER JOIN stars ON (movies.id = stars.movie_id)
    INNER JOIN people ON (stars.person_id = people.id)
    INNER JOIN ratings ON (movies.id = ratings.movie_id)

WHERE
    people.name = "Chadwick Boseman"

ORDER BY
    ratings.rating DESC

LIMIT 5;