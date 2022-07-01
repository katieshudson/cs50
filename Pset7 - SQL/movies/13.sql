-- write a SQL query to list the names of all people who starred in a movie in which Kevin Bacon also starred.

-- METHOD 1
-- Query 1 - list out the actors' names but do not include Kevin Bacon based on the movie ids from the nested query
-- (write this first) - Nested Query (query 2) --> list out the movies that Kevin Bacon born in 1958 has been in

SELECT
    people.name

FROM
    people

INNER JOIN stars ON people.id = stars.person_id

WHERE NOT (people.name = "Kevin Bacon" AND people.birth = "1958")

    AND stars.movie_id IN (  -- list out the movies that Kevin bacon has been in

        SELECT
            stars.movie_id  -- lists out the movie id's

        FROM
            people

        INNER JOIN stars ON people.id = stars.person_id

        WHERE
            people.name = "Kevin Bacon" AND people.birth = "1958"  -- specifying the right Kevin Bacon
    )

ORDER BY people.name;



-- -- METHOD 2
-- -- using table alias names

-- SELECT
-- --    people.name
-- --    stars.movie_id  -- lists out the movie id's
-- main_actors.id AS main_actors_id,
-- main_actors.name AS main_actors_name,
-- main_actors.birth AS main_actors_birth,
-- stars.movie_id AS actor_movie_id,
-- costars.movie_id AS costars_movie_id,
-- costars.person_id AS costars_person_id,
-- costars_bio.name AS costar_name,
-- costars_bio.birth AS costars_birth

-- FROM
--     people AS main_actors

-- INNER JOIN stars ON main_actors.id = stars.person_id
-- INNER JOIN stars AS costars ON stars.movie_id = costars.movie_id
-- INNER JOIN people AS costars_bio ON costars_bio.id = costars.person_id

-- WHERE
--     main_actors.name = "Kevin Bacon" AND main_actors.birth = 1958
--     AND NOT (costars_bio.name = "Kevin Bacon" AND costars_bio.birth = 1958)
-- -- ORDER BY people.name;

-- ;