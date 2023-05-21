CREATE TABLE "problems" (
    "id" INTEGER NOT NULL UNIQUE,
    "title" TEXT NOT NULL,
    "description" TEXT NOT NULL,
    "input" TEXT,
    "output" TEXT,
    "range" TEXT,
    "hint" TEXT,
    "samples" INTEGER,
    "testCases" INTEGER NOT NULL,
    PRIMARY KEY("id" AUTOINCREMENT)
)
