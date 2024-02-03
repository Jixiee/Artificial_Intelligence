import heapq

class PuzzleState:
    def __init__(self, puzzle, parent=None, move="Initial"):
        self.puzzle = puzzle
        self.parent = parent
        self.move = move
        self.cost = self.calculate_cost()

    def __lt__(self, other):
        return self.cost < other.cost

    def calculate_cost(self):
        # Implementing the Manhattan Distance heuristic
        total_cost = 0
        for i in range(3):
            for j in range(3):
                if self.puzzle[i][j] != 0:
                    row, col = divmod(self.puzzle[i][j] - 1, 3)
                    total_cost += abs(i - row) + abs(j - col)
        return total_cost

    def get_blank_position(self):
        for i in range(3):
            for j in range(3):
                if self.puzzle[i][j] == 0:
                    return i, j

    def generate_neighbors(self):
        neighbors = []
        row, col = self.get_blank_position()

        for move in [(0, 1), (0, -1), (1, 0), (-1, 0)]:
            new_row, new_col = row + move[0], col + move[1]

            if 0 <= new_row < 3 and 0 <= new_col < 3:
                new_puzzle = [list(row) for row in self.puzzle]
                new_puzzle[row][col], new_puzzle[new_row][new_col] = new_puzzle[new_row][new_col], new_puzzle[row][col]
                neighbors.append(PuzzleState(new_puzzle, self, move))

        return neighbors

def best_first_search(initial_state):
    heap = [initial_state]
    visited = set()

    while heap:
        current_state = heapq.heappop(heap)

        if current_state.puzzle == goal_state:
            return current_state

        visited.add(tuple(map(tuple, current_state.puzzle)))

        for neighbor in current_state.generate_neighbors():
            if tuple(map(tuple, neighbor.puzzle)) not in visited:
                heapq.heappush(heap, neighbor)

    return None

def print_solution(solution_state):
    path = []
    while solution_state:
        path.append(solution_state.puzzle)
        solution_state = solution_state.parent

    for t in path[::-1]:
        print("\n".join([" ".join(map(str, row)) for row in t]))
        print("\n---\n")

if __name__ == "__main__":
    initial_state = PuzzleState([[1, 2, 3], [4, 0, 5], [6, 7, 8]])
    goal_state = [[1, 2, 3], [4, 5, 6], [7, 8, 0]]

    solution_state = best_first_search(initial_state)

    if solution_state:
        print("Solution found:")
        print_solution(solution_state)
    else:
        print("No solution found.")
