class CourseGraph:
    def add_prerequisite(self, pre_course, post_course):
        # 添加边
        pass
    def topological_sort(self):
        # Kahn算法实现
        pass
        
def assign_semesters(sorted_courses, max_credits_per_semester):
    # 遍历排序后课程，按学分上限分配到各学期
    # 返回 {学期1:[课程列表], 学期2:[...]}
    pass

def generate_variations(course_graph, num_variants=50):
    # 通过随机选择或优先级调整生成多个拓扑排序
    pass