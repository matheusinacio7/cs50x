-- Active: 1657258549497@@127.0.0.1@3306
SELECT m.title FROM people AS p
  JOIN stars AS s ON p.id = s.person_id
  JOIN movies AS m ON m.id = s.movie_id
  JOIN ratings AS r ON m.id = r.movie_id
  WHERE p.name = 'Chadwick Boseman'
  ORDER BY r.rating DESC
  LIMIT 5;