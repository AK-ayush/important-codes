import math

def solution(dimensions, your_position, guard_position, distance):

    if not is_strong(your_position, guard_position, distance):
        return 0
    x_itr = int(math.ceil((your_position[0]+distance)/dimensions[0]))
    y_itr = int(math.ceil((your_position[1]+distance)/dimensions[1]))

    # reflections of guard_position
    positions = []
    positions_x = mirror_x(guard_position, dimensions, x_itr)
    for pos in positions_x:
        positions_y = mirror_y(pos, dimensions, y_itr)
        positions += positions_y

    cand_postions_guard = []
    for pos in positions:
        cand_postions_guard += [pos, [-1*pos[0], pos[1]], [-1*pos[0], -1*pos[1]], [pos[0], -1*pos[1]]]

    # reflections of your_position
    positions = []
    positions_x = mirror_x(your_position, dimensions, x_itr)
    for pos in positions_x:
        positions_y = mirror_y(pos, dimensions, y_itr)
        positions += positions_y

    cand_postions_your = []
    for pos in positions:
        cand_postions_your += [pos, [-1*pos[0], pos[1]], [-1*pos[0], -1*pos[1]], [pos[0], -1*pos[1]]]


    visited_self = {}
    for yp in cand_postions_your:
        if yp == your_position:
            continue
        dist = get_dist(your_position, yp)
        angle = math.atan2(yp[1]-your_position[1], yp[0]-your_position[0])
        if angle not in visited_self or visited_self[angle] > dist:
            visited_self[angle] = dist

    # apply checkks in candidate postions
    answer = 0
    visited = {} # remove the duplicate points which are on boundry of room
    visited[tuple(your_position)] = True

    visited_angle = {}
    angle_dict = corner_angles(dimensions, your_position) # for corner
    for pos in cand_postions_guard:
        t_pos = tuple(pos)
        if t_pos in visited:
            continue
        else:
            visited[t_pos] = True
        dist = get_dist(your_position, pos)
        if dist <= (distance**2): # and not colinear(your_position, guard_position, pos):
            angle = math.atan2(pos[1]-your_position[1], pos[0]-your_position[0])
            if angle not in visited_angle and (angle not in visited_self or visited_self[angle]>dist):
                visited_angle[angle] = True
                if angle in angle_dict:
                    # print "corner", angle, pos, angle_dict[angle]
                    continue
                # print angle, pos
                answer += 1
    # print visited_angle
    return answer

def mirror_x(p, dimensions, x_itr):
    postions = [p]
    prev = p
    for i in range(x_itr):
        dx = (i+1)*dimensions[0] - prev[0]
        # dy = dimensions[1] - prev[1]
        nxt = [prev[0]+2*dx, prev[1]]
        postions.append(nxt)
        prev = nxt
    return postions


def mirror_y(p, dimensions, y_itr):
    postions = [p]
    prev = p
    for i in range(y_itr):
        dy = (i+1)*dimensions[1] - prev[1]
        nxt = [prev[0], prev[1]+2*dy]
        postions.append(nxt)
        prev = nxt
    return postions


def is_strong(p1, p2, distance):
    return distance**2 >= ((p2[0]-p1[0])**2 + (p2[1]-p1[1])**2)

def get_dist(p1, p2):
    return (p2[0]-p1[0])**2 + (p2[1]-p1[1])**2


def corner_angles(dim, p):
    corners = [[0,0], [dim[0], 0], [0, dim[0]], dim]
    angle_dict = {}
    for i,c in enumerate(corners):
        angle = math.atan2(c[1]-p[1], c[0]-p[0])
        angle_dict[angle]=i
    return angle_dict

# def colinear(p1, p2, p3):
#     x1, y1 = p2[0]-p1[0], p2[1]-p1[1]
#     x2, y2 = p3[0]-p2[0], p3[1]-p2[1]
#     return abs(x1 * y2 - x2 * y1) < 1e-12


# print solution([300,275], [150,150], [185,100], 500)
# print solution([42, 59], [34, 44], [6, 34], 5000)
# print solution([2,5], [1,2], [1,4], 11)
# print solution([3,2], [1,1], [2,1], 4)

# print math.atan2(0, -1)
# print math.atan2(1-1, 1+2)
