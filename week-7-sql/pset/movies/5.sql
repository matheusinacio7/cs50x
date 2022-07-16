-- Active: 1657258549497@@127.0.0.1@3306
SELECT title, year FROM movies
  WHERE title LIKE "Harry Potter%"
  ORDER BY year ASC;