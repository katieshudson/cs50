SELECT
    AVG(rating)
from
    ratings
WHERE
    movie_id IN (
        SELECT
            id
        FROM
            movies
        WHERE
            year = "2012"
    );