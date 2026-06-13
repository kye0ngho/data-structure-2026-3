A = {
    0: [1, 2, 3],
    1: [0, 2, 4, 5],
    2: [0, 1, 6],
    3: [0],
    4: [1],
    5: [1],
    6: [2]
}

def bfs(A):
    '''
    queue 를 리스트로 정의 및 첫 요소를 0으로 정의합니다. 해당 위치는 시작점이기 때문에 visited 에 0을 추가합니다.
    while 에서 조건에 리스트가 들어갈 경우 리스트가 비어있으면 False 이기에 반복이 중단됩니다. 즉 while queue 를 사용하여 queue 가
    요소가 없이 비었을 때까지 반복을 하도록 구현하였습니다.

    FIFO 즉 선입선출 형태로 구현하기 위해 pop(0)로 0번 index 즉 front 값이 pop 되어 node 에 저장 되도록 하였고 answer라는 리스트에 pop 된 값을 append 하였습니다.
    입력은 tail( 끝 ) 에 되고 , 출력은 front 에서 하기 위해 append 와 pop(0) 를 활용하였습니다.

    A ( 입력 ) 의 node 의 이웃 노드들을 neighbor 에 넣고 , 해당 부분이 방문되지 않았을 시에 방문 및 append 를 통해서 queue 에 저장하게 됩니다.

    '''
    answer = []
    visited = set()
    queue = [0]
    visited.add(0)
    while queue:
        node = queue.pop(0)
        answer.append(node)
        for neighbor in A[node]:
            if neighbor not in visited:
                visited.add(neighbor)
                queue.append(neighbor)
    return answer

    # BFS 는 queue 를 통해 구현 FIFO 구조로 먼저 들어온 노드가 먼저 pop 되도록 구현



def dfs(A):
    '''
    DFS 는 stack 을 통하여 구현했습니다. 동일하게 visited 를 set() 으로 정의하고 , stack을 리스트로 정의 및 초기값을 0 으로 정의하였습니다.
    그 이후 visited 에 0을 더해주었습니다.
    BFS 와 동일하게 stack 이란 리스트가 비어 ( False ) 있지 않을 때까지 반복하였고
    LIFO 즉 나중에 들어온 노드가 먼저 pop 이 되도록 pop() 함수를 index 없이 사용하여 마지막 요소를 삭제 및 반환하도록 하였습니다.
    또한 반환된 값을 answer에 append 하여 answer 리스트의 끝부분(tail) 에 입력되도록 하였습니다. append 와 pop 이 동일한 구간 ( 각각 answer 리스트와 stack 의 끝부분, tail ) 에서 이루어져 나중에 들어온 노드가
    먼저 나가도록 LIFO 를 구현하였습니다.
    A[node] 즉 현재 노드와 연결된 이웃 노드를 방문할 때 reversed 를 활용해서 순서를 반대로 변경하였습니다.
    그 이후에는 해당 이웃 노드가 방문되지 않았다면 visited 에 더하여 방문으로 바꾸고 , stack 에 append 하여 노드를 저장하였습니다.



    '''
    answer = []
    visited = set()
    stack = [0]
    visited.add(0)
    while stack:
        node = stack.pop()
        answer.append(node)
        for neighbor in reversed(A[node]):
            if neighbor not in visited:
                visited.add(neighbor)
                stack.append(neighbor)
    return answer


# DFS 는 stack 을 통해 구현 LIFO 구조로 나중에 들어온 노드가 먼저 pop 되도록 구현
# 아래는 체크함수입니다. 수정하실 필요 없습니다.
bfs_result = bfs(A)
dfs_result = dfs(A)

assert bfs_result == [0,1,2,3,4,5,6]
assert dfs_result == [0,1,4,5,2,6,3]
print('PASSED!')
