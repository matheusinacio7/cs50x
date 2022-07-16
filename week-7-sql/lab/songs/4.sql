-- Active: 1657258549497@@127.0.0.1@3306
SELECT name FROM songs
  WHERE
    danceability > 0.75 AND
    energy > 0.75 AND
    valence > 0.75;
