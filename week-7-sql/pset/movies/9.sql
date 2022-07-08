-- Active: 1657258549497@@127.0.0.1@3306
SELECT DISTINCT(p.name) FROM people AS p
  JOIN stars AS s ON p.id = s.person_id
  JOIN movies AS m ON m.id = s.movie_id
  WHERE m.year = 2004
  ORDER BY p.birth ASC;