-- CREATE TABLE `users` (
--     `id` INTEGER NOT NULL UNIQUE AUTO_INCREMENT,
--     `username` VARCHAR(32) NOT NULL UNIQUE,
--     `password` TEXT NOT NULL,
--     `nickname` TEXT NOT NULL,
--     `email` TEXT NOT NULL,
--     `privilege` INTEGER NOT NULL DEFAULT 0,
--     PRIMARY KEY(`id`),
--     INDEX(`username`)
-- );
CREATE TABLE `users` (
    `id` INTEGER NOT NULL UNIQUE,
    `username` TEXT NOT NULL UNIQUE,
    `password` TEXT NOT NULL,
    `nickname` TEXT NOT NULL,
    `email` TEXT NOT NULL,
    `privilege` INTEGER NOT NULL DEFAULT 0
);
