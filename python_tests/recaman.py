import turtle

front = 1
back = 0

class Recaman:
    def __init__(self, end):
        self.visited = {1:True}
        self.start = 1
        self.end = end
        self.i = 1
        self.curr = 1
        self.curve = True
        self.direction = back
        self.turtle = turtle

        self.turtle.left(90)

    def next_reacaman(self):
        self.curve = not self.curve
        self.direction = back
        next = self.curr
        next -= self.i
        if next <= 0 or next in self.visited:
            self.direction = front
            next += 2*self.i
        self.curr = next

        self.visited[self.curr] = True
        self.i+=1

    def display_curr(self):
        print(self.i, self.curr, self.direction, self.curve)
        if self.curve:
            degree = 180
        else:
            degree = 0

        self.turtle.left(degree)

        self.turtle.circle(self.i * 10, 180)


recaman = Recaman(10)
for i in range(6):
    recaman.display_curr()
    recaman.next_reacaman()

turtle.done()

# turtle.left(90)
#
# turtle.circle(10, 180)
# turtle.left(180)
# turtle.circle(20, 180)
# turtle.left(180)
# turtle.circle(40, 180)
# turtle.left(0)
# turtle.circle(70, 180)
#
# turtle.done()
