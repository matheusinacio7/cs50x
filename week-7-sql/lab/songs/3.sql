-- Active: 1657258549497@@127.0.0.1@3306
SELECT name FROM songs
  ORDER BY duration_ms DESC
  LIMIT 5;