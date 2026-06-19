#pragma once
#include <QString>
#include <QVector>
#include <QMap>
#include <QPair>
#include <cstring>

#define MAX_AIRPORTS 20 //최대 공항 수

// 공항 정보를 표현하는 구조체 정의
struct Airport {
    QString code; //공항 코드
    QString name; //공항 이름, ex ) 인천국제공항
    QString city; //도시명, ex ) 인천
};

//항공편 정보를 저장하는 구조체
struct Flight {
    int src; //출발 공항 인덱스
    int dst; //도착 공항 인덱스
    QString number;//항공편 번호 
    QString airline;//항공사명 
    QString depTime;//출발 시간
    QString arrTime;//도착 시간
    int price;//가격
    int duration;//소요 시간

    Flight(int s, int d, const QString& num, const QString& air,
           const QString& dep, const QString& arr, int p, int dur)
        : src(s), dst(d), number(num), airline(air),
          depTime(dep), arrTime(arr), price(p), duration(dur) {}
};

// 인접 행렬 기반 공항 그래프 클래스 정의. 기존 수업시간에 진행한 WGraph는 adj[i][j]에 가중치(int) 하나만 저장,
// 같은 구간(i→j)에 항공편이 여러 개 존재할 수 있는 가능성 존재.
// adj[i][j]는 노선 존재 여부(True or False)만 저장.
// 항공편 상세 정보(편명, 가격, 소요시간 등)는 flightMap에 별도로 저장하는 방식으로 확장하여 관리.
class AirportGraph {
    int size;  // 현재 등록된 공항 수, 공항 그래프의 노드 수
    Airport airports[MAX_AIRPORTS]; // 공항 배열(노드)
    bool adj[MAX_AIRPORTS][MAX_AIRPORTS];// 인접 행렬 (간선 존재 여부, 간선이 존재하면 True , 존재하지 않으면 False)
    QMap<QPair<int,int>, QVector<Flight>> flightMap; // (출발, 도착) 쌍에 대한 항공편 목록

public:
    //생성자: 인접 행렬을 false로 초기화.
    //그래프를 비워두기 . 이후에 addAirport ( 노드 추가 ) , addFlight ( 간선 추가 )로 업데이트.
    AirportGraph() : size(0) {
        memset(adj, false, sizeof(adj));
    }

    //공항(노드) 추가하는 함수.
    void addAirport(const QString& code, const QString& name, const QString& city) {
        if (size < MAX_AIRPORTS)
            airports[size++] = {code, name, city};
    }

    //항공편(간선) 추가:인접 행렬에 표시하고 항공편 목록에 저장하는 함수.
    void addFlight(const Flight& f) {
        adj[f.src][f.dst] = true;
        flightMap[{f.src, f.dst}].append(f);
    }

    //현재 공항 수. 즉 현재 공항 그래프의 노드 개수 반환.
    int getSize() const { return size; }

    //인덱스로 공항 정보 반환.
    Airport getAirport(int i) const { return airports[i]; }

    //두 공항 사이 직항 노선 존재하는지 여부 bool 으로 반환. 
    bool hasRoute(int src, int dst) const { return adj[src][dst]; }

    //특정 공항에서 출발하는 모든 항공편 반환.
    QVector<Flight> getFlightsFrom(int src) const {
        QVector<Flight> result;
        for (int dst = 0; dst < size; dst++)
            if (adj[src][dst])
                result += flightMap.value({src, dst});
        return result;
    }

    //특정한 공항에 도착하는 모든 항공편들 ( 간선 ) 반환.
    QVector<Flight> getFlightsTo(int dst) const {
        QVector<Flight> result;
        for (int src = 0; src < size; src++)
            if (adj[src][dst])
                result += flightMap.value({src, dst});
        return result;
    }
};
