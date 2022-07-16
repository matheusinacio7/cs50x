-- Active: 1657258549497@@127.0.0.1@3306
SELECT DISTINCT(p.name) FROM
    ( SELECT * FROM movies AS m
      JOIN stars AS s ON m.id = s.movie_id
      JOIN people AS p ON p.id = s.person_id
      WHERE p.name = 'Kevin Bacon'
    ) AS kbm
  JOIN movies AS m ON m.id = kbm.movie_id
  JOIN stars AS s ON m.id = s.movie_id
  JOIN people AS p ON p.id = s.person_id
  WHERE p.name != 'Kevin Bacon';
