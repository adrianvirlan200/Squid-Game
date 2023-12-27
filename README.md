# Squid Game- OOP Project
The year 2021 was full of surprises, one of them represented by the South Korean series "Squid Game". Your goal is to recreate your game logic from the series using OOP concepts.

The requirements you received from the game creator are as follows:

The application must store the data of the people who will participate in the games. The required data are as follows: name, first name, town, debt money (randomly allocated between 10,000 and 100,000), weight (randomly assigned between 50 and 100)

There will be a total of 108 users in the application
Users will be of two types, each with other specific details: competitor: contest number and supervisor: mask shape(rectangle, triangle, circle)
The 108 users will be randomly divided into two classes as follows:

99 competitors. Competitors will receive an increasing number between 1 and 99
9 supervisors. Supervisors will be divided into 3 equal random groups for each form

Competitors will be divided equally between the 3 groups of supervisors so that each competitor has a supervisor. Each supervisor will have the same number of competitors.

Once divided, users will start the games.

# The first game is "Red Light Green Light"

In the first game, all users with an even number will be eliminated. Show who's left

# The second game is "Tug of War"

Players will be randomly divided into 4 equal teams. If there are players who do not join a team, they go straight to the next stage. Two by two, the teams will duel, being eliminated the one with the lowest weight. When a team is eliminated, all its players are eliminated .Show who's left
    
# The third game is "Marbles"

The remaining players will be divided into pairs of two, each of which will generate a random number, and the one with the smaller number will move on. If the number of players reached in this stage is odd, the one left out automatically goes to the next stage. Show who's left

# The last stage, the fourth game, is "Genken", or "Stone, Paper, Scissors"

Starting in descending order of competition numbers, players will duel (1vs1) one at a time at Genken. Each move has an associated number, stone = 1, paper = 2, scissors = 3. The number chosen by each player is random. It is played until one player is eliminated and the next one is left until there is only one winner left. Show who's left

The winner will receive as a reward the sum of all the debts of the other competitors.

Each supervisor will receive the amount corresponding to the eliminated players who belonged to him. The supervisor who has the winner will receive his debt multiplied by 10. From the amounts received, their initial debt is deducted and thus it is found how much is left to each.

At the end to display:

how much the winning competitor won

display in descending order the amount earned by the supervisors and their amounts.

to show which team of supervisors raised the most money
