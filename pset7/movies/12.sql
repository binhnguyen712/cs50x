SELECT title FROM movies WHERE EXISTS (SELECT 1 FROM stars JOIN people ON stars.person_id = people.id WHERE movies.id = stars.movie_id AND name = 'Bradley Cooper') AND EXISTS (SELECT 1 FROM stars JOIN people ON stars.person_id = people.id WHERE movies.id = stars.movie_id AND name = 'Jennifer Lawrence');
