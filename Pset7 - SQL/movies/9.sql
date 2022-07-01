SELECT
    DISTINCT people.name
FROM
    movies
    INNER JOIN stars ON movies.id = stars.movie_id
    JOIN people ON stars.person_id = people.id
WHERE
    movies.year = "2004"
ORDER BY
    people.birth ASC;


/* 2nd method:
SELECT
    DISTINCT name
FROM
    people
WHERE
    people.id IN (
        SELECT
            people.id
        FROM
            movies
            INNER JOIN stars ON movies.id = stars.movie_id
            JOIN people ON stars.person_id = people.id
        WHERE
            movies.year = "2004"

)
ORDER BY
    people.birth

; */