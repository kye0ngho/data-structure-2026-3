import sys

## 입력 받는 코드입니다. 수정할 필요 없습니다.
sys.stdin = open('case.txt')
N, M = list(map(int,input().split()))
print(N, M)
concerts = []
for v in range(N):
    values = list(map(int, input().split()))
    concerts.append(values)
# print(concerts)
# [[1, 0, 0, 1, 1, 0], [1, 0, 1, 1, 0, 0], [1, 1, 1, 1, 0, 1], [0, 1, 1, 0, 1, 1], [0, 1, 0, 0, 1, 0]]
###################################

def count_stages(concerts):
    answer = 0
    N = len(concerts)
    M = len(concerts[0])
    visited = [[False] * M for _ in range(N)]
    '''
    N은 콘서트 장의 세로 길이입니다 . 즉 행의 개수에 대한 변수입니다.
    M은 콘서트 장의 가로 길이입니다 . 열의 개수를 저장하고 있는 변수입니다.
    [0] 으로 첫번째 행 벡터를 불러온 후 행 벡터의 길이를 len 함수를 이용하여 열의 개수를 저장하였습니다.

    visited 를 정의 및 반복문을 활용하여 NxM 행렬의 False 행렬로 초기화 하였습니다.

    '''

    def bfs(r, c):
        ''' queue 를 입력받은 row , column 값의 튜플 형태로 정의를 하였고
                    해당 행 , 열 위치를 방문하였기 때문에 True ( 위의 코드에서 False 로 초기화 ) 로 바꾸어 주었습니다.
                    BFS 이기 때문에 FIFO 즉 선입선출 식으로 먼저 들어온 행열 값이 먼저 나가도록 queue 로 구현하였습니다.

                    (-1,0),(1,0),(0,-1),(0,1) 는 각각 행-1 , 행+1, 열-1,열+1 (위, 아래, 왼쪽, 오른쪽 ) 으로 탐색하도록 반복하였고
                    현재의 row 와 col 에서 해당 위치로 이동하면서 nr , nc 즉 새로운 row 와 col 이 N,M 행렬 사이즈를 벗어나지 않고,
                    방문하지 않았고 , 0 ( 방문 가능한 위치 ) 일 시 해당 위치를 방문 True 로 수정 및 queue 에 enqueue 하도록 구현하였습니다.

        '''
        queue = [(r, c)]
        visited[r][c] = True
        while queue:
            row, col = queue.pop(0)
            for dr, dc in [(-1,0),(1,0),(0,-1),(0,1)]:
                nr, nc = row+dr, col+dc
                if 0 <= nr < N and 0 <= nc < M and not visited[nr][nc] and concerts[nr][nc] == 0:
                    visited[nr][nc] = True
                    queue.append((nr, nc))



    '''
    N,M 입력받은 행렬의 행, 열 만큼 반복 ( 모든 구간을 탐색하기 위해 )
    concerts[r][c] 입력받은 콘서트 장의 행 (r) ,열 (c) 이 0 즉 방문 가능한 상태 그리고 not 해당 위치가 방문되지 않았을 때 (not 이기에 False 여야 True 로 작동
    and 이기 때문에 concerts[r][c] 와 visited[r][c] 가 모두 True 여야 조건문 아래 블럭 실행합니다.) 해당 위치에서 다시 bfs 를 호출하고 , bfs 를 호출한 것은
    방문하지 않은 연결된 0들 ( 무대로 활용 가능한 부분 ) 을 찾았다는 것이므로 해당 위치에서 무대를 하나 만들 수 있는 것을 의미하기에 answer 를 1 증가시킵니다.
    반복문이 끝났을 때 마지막으로 answer 를 return 하여 독립적으로 설치 가능한 무대의 개수를 반환합니다.

    '''
    for r in range(N):
        for c in range(M):
            if concerts[r][c] == 0 and not visited[r][c]:
                bfs(r, c)
                answer += 1
    return answer



print(count_stages(concerts))
