-- write a SQL query to list the titles of all movies in which both Johnny Depp and Helena Bonham Carter starred.

-- STEPS
-- 1) list of movies of johnny depp
-- 2) list of movies of helena b c
-- 3) combine 1 + 2 with WHERE people.name = Johnny Depp AND bonham carter
--      --> use IN with WHERE to select multiple values for people.name
--      --> then group by movies.id for the same movies, and use count to ensure that the 2 names appear for the grouping of movies

SELECT
    movies.title

FROM
    movies

INNER JOIN stars ON movies.id = stars.movie_id
INNER JOIN people ON stars.person_id = people.id

WHERE
    people.name IN ("Helena Bonham Carter", "Johnny Depp")

GROUP BY movies.id

HAVING COUNT (*) = 2

ORDER BY movies.title ASC;