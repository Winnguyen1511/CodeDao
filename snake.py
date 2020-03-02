import curses, time
import random

UP, DOWN, RIGHT, LEFT, ESC = 1,-1,2,-2,0
HEAD = 0
#Init the screen:
s = curses.initscr()
#Set cursor to invisible (0)
curses.curs_set(0)
#Get max height and width:
sh, sw = s.getmaxyx()
#Create new window in the terminal
w = curses.newwin(sh, sw, 0 , 0)
w.keypad(True)
w.timeout(100)

#addch(row, col, symbol)
def draw(win, obj):
    win.addch(obj.y, obj.x, obj.sym)
def erase(win, obj):
    win.addch(obj.y, obj.x, " ")
class food:
    def __init__(self, screen):
        maxHeight, maxWidth = screen.getmaxyx()
        self.x = random.randint(1, maxWidth-1)
        self.y = random.randint(1, maxHeight-1)
        self.sym = '*'


class snakeNode:
    def __init__(self, x, y, sym):
        self.x = int(x)
        self.y = int(y)
        self.sym = str(sym)

class snake:
    def __init__(self, screen, window):
        self.dir = RIGHT

        self.maxHeight, self.maxWidth = screen.getmaxyx()
        headX = random.randint(1,self.maxWidth-1)
        headY = random.randint(1, self.maxHeight-1)
        
        head = snakeNode(headX, headY, ">")
        self.body = [head]
        self.lenght = len(self.body)
        #self.body.append(head)
        self.window = window
        #display()
    def display(self):
        for i in range(0, len(self.body)):
            draw(self.window, self.body[i])
    def move(self, dir):
        #if (dir != self.dir) and (dir != -self.dir):
        if (dir != -self.dir):
            self.dir = dir
        mod = [0,0]
        headSym = ">"
        if self.dir == UP:
            mod[1] = -1
            headSym = "^"
        elif self.dir == DOWN:
            mod[1] = 1
            headSym = "v"
        elif self.dir == RIGHT:
            mod[0] = 1
            headSym = ">"
        elif self.dir == LEFT:
            mod[0] = -1
            headSym = "<"
        newX = self.body[HEAD].x + mod[0]
        newY = self.body[HEAD].y + mod[1]
        if newX >= self.maxWidth:
            newX = 0 + mod[0]
        elif newX <= 0:
            newX = self.maxWidth + mod[0]

        if newY >= self.maxHeight:
            newY = 0 + mod[1]
        elif newY <= 0:
            newY = self.maxHeight + mod[1]
        
        newHead = snakeNode(newX, newY, headSym)
        self.body[HEAD].sym = "o"
        self.body.insert(HEAD, newHead)
        erase(self.window, self.body.pop())
    def eat(self, food):
        if self.body[HEAD].x == food.x and self.body[HEAD].y == food.y:
            #newNode = snakeNode()
            mod = [0,0]
            headSym = ">"
            if self.dir == UP:
                mod[1] = -1
                headSym = "^"
            elif self.dir == DOWN:
                mod[1] = 1
                headSym = "v"
            elif self.dir == RIGHT:
                mod[0] = 1
                headSym = ">"
            elif self.dir == LEFT:
                mod[0] = -1
                headSym = "<"
            newX = self.body[HEAD].x + mod[0]
            newY = self.body[HEAD].y + mod[1]
            if newX >= self.maxWidth:
                newX = 0 + mod[0]
            elif newX <= 0:
                newX = self.maxWidth + mod[0]

            if newY >= self.maxHeight:
                newY = 0 + mod[1]
            elif newY <= 0:
                newY = self.maxHeight + mod[1]
            self.body[HEAD].sym = "o"
            newNode = snakeNode(newX, newY, headSym)
            self.body.insert(HEAD, newNode)
            self.lenght = len(self.body)
            return True
        return False


fd = food(s)
draw(w, fd)

sn = snake(s, w)
sn.display()

snake_dir = RIGHT
key = curses.KEY_RIGHT
while True:
    sn.move(snake_dir)
    sn.display()
    next_key = w.getch()
    if next_key == -1:
        key = key
    else:
        key = next_key
    if sn.eat(fd) == True:
        fd = food(s)
        draw(w, fd)
    for i in range(1, sn.lenght):
        if sn.body[0].x == sn.body[i].x and sn.body[0].y == sn.body[i].y:
            curses.endwin()
            quit()

    if key == curses.KEY_UP:
        snake_dir = UP
    elif key == curses.KEY_DOWN:
        snake_dir = DOWN
    elif key == curses.KEY_RIGHT:
        snake_dir = RIGHT
    elif key == curses.KEY_LEFT:
        snake_dir = LEFT
    elif key == curses.KEY_BACKSPACE:
        break

curses.endwin()
quit()