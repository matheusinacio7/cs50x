-- Active: 1657258549497@@127.0.0.1@3306
SELECT AVG(r.rating) FROM movies AS m
  JOIN ratings AS r ON r.movie_id = m.id
  WHERE year = 2012;