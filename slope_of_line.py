def calculate_line(point1, point2, c):
    x1, y1 = point1
    x2, y2 = point2
    slope = (y1 - y2) / (x1 - x2)
    print("y = {}x + {}".format(slope, c))
