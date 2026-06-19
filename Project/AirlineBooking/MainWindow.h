#pragma once
#include <QMainWindow>
#include <QLabel>
#include <QListWidget>
#include <QVector>
#include "Graph.h"
#include "MapWidget.h"

// QMainWindow 상속: loadData()로 AirportGraph 초기화 setupUI()로 QHBoxLayout 기반 레이아웃 구성
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    //슬롯: MapWidget::airportClicked(int) 수신 → getFlightsFrom/To 조회 후 QListWidget 갱신 합니다.
    void onAirportClicked(int index);

    //슬롯: QListWidget::itemClicked(QListWidgetItem*) 수신 → QMessageBox로 예매 완료 출력 합니다.
    void onFlightClicked(QListWidgetItem* item);

private:
    void setupUI();   // QHBoxLayout으로 좌(MapWidget) + 우(QFrame) 분할 레이아웃 생성
    void loadData();  // AirportGraph에 addAirport(노드)/addFlight(간선) 등록

    AirportGraph* graph;  //인접 행렬 기반 공항 그래프 (노드: 공항, 간선: 항공편)

    MapWidget* mapWidget;          //왼쪽: QWidget 상속, QPainter로 지도·노선 렌더링

    QLabel* airportNameLabel;      //선택 공항명 표시 및 onAirportClicked에서 setText() 호출
    QLabel* depCountLabel;         //출발편 수 표시
    QListWidget* depList;          //출발편 목록, addItem()으로 항목 추가
    QLabel* arrCountLabel;         //도착편 수 표시
    QListWidget* arrList;          //도착편 목록, addItem()으로 항목 추가

    // onFlightClicked에서 row 인덱스로 Flight 객체에 접근하기 위해 멤버로 보관합니다.
    QVector<Flight> depFlights;
    QVector<Flight> arrFlights;
};
