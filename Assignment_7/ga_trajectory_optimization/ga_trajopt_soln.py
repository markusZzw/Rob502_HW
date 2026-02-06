import numpy as np
from ga_trajopt import GATrajectoryOptimizer


class GATrajectoryOptimizerSolution(GATrajectoryOptimizer):

    def fitness(self, x):
        fit = 0
        # --- Your code here
        full_path = np.vstack([self.start, x])
        positions = np.cumsum(full_path, axis=0)
        final_position = positions[-1]
        goal_distance = np.sum((final_position - self.goal) ** 2)
        term1 = -goal_distance
        displacements = np.sum(x ** 2, axis=1)
        term2 = np.sum(displacements)
        collision_count = 0

        for t in range(len(positions)):
            point = positions[t]
            in_obstacle = False
            for center, radius in zip(self.obstacle_centres, self.obstacle_radii):
                distance = np.linalg.norm(point - center)
                if distance < radius:
                    in_obstacle = True
                    break 
            if in_obstacle:
                collision_count += 1

        term3 = 100 * collision_count
        fit = term1 -term2 - term3
        # ---
        return fit

    def crossover(self, parent1, parent2, crossover_point):
        child1, child2 = None, None
        # --- Your code here
        K = crossover_point
        child1 = np.vstack([parent1[:K], parent2[K:]])
        child2 = np.vstack([parent2[:K], parent1[K:]])
        # ---
        return child1, child2

    def select_children(self, parent, child):

        chosen, fitness = None, None

        # --- Your code here
        parent_fitness = self.fitness(parent)
        child_fitness = self.fitness(child)
        r = np.random.rand()
        if r < self.params['select_best_child_p']:
            if child_fitness > parent_fitness:
                chosen = child
                fitness = child_fitness
            else:
                chosen = parent
                fitness = parent_fitness
        else:
            if child_fitness < parent_fitness:
                chosen = child
                fitness = child_fitness
            else:
                chosen = parent
                fitness = parent_fitness
        # ---
        return chosen, fitness


if __name__ == "__main__":
    # GA path planning

    # Setup start, goal and spherical obstacles
    goal = np.array([1.0, 1.0])
    start = np.array([0.0, 0.0])
    obstacle_centres = np.array([
        [0.5, 0.2],
        [0.2, 0.8]
    ])
    obstacle_radii = np.array([0.25, 0.15])

    # Solver parameters
    N = 500
    T = 20
    params = {
        'N': 500,
        'iters': 100,
        'cross_over_p': 0.5,
        'mutate_p': 0.5,
        'select_best_parent_p': 0.9,
        'select_best_child_p': 0.9
    }

    solver = GATrajectoryOptimizerSolution(start, goal, obstacle_radii, obstacle_centres, T, params)
    # Solve to get best trajectory and plot
    best = solver.solve()
    solver.plot_trajectory(best)
