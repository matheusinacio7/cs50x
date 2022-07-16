-- Active: 1657258549497@@127.0.0.1@3306
SELECT DISTINCT(p.name) FROM people AS p
  JOIN directors AS d ON p.id = d.person_id
  JOIN ratings AS r ON r.movie_id = d.movie_id
  WHERE r.rating >= 9.0;