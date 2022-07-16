-- Active: 1657258549497@@127.0.0.1@3306
SELECT jdm.title FROM
    ( SELECT * FROM movies AS m
      JOIN stars AS s ON m.id = s.movie_id
      JOIN people AS p ON p.id = s.person_id
      WHERE p.name = 'Johnny Depp'
    ) AS jdm
  JOIN
    ( SELECT * FROM movies AS m
      JOIN stars AS s ON m.id = s.movie_id
      JOIN people AS p ON p.id = s.person_id
      WHERE p.name = 'Helena Bonham Carter'
    ) AS hbcm
  ON jdm.movie_id = hbcm.movie_id;