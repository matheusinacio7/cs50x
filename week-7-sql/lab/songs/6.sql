-- Active: 1657258549497@@127.0.0.1@3306
SELECT s.name FROM songs AS s
  JOIN artists AS a ON s.artist_id = a.id
  WHERE a.name = 'Post Malone';