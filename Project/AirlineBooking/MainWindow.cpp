#include "MainWindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFrame>
#include <QMessageBox>
#include <QFont>

// 생성자: graph 포인터를 nullptr로 초기화한 뒤,
// loadData()로 AirportGraph에 노드(공항)/간선(항공편) 데이터를 등록하고,
// setupUI()로 QMainWindow의 중앙 위젯에 QHBoxLayout 기반 좌우 분할 레이아웃을 구성함
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), graph(nullptr)
{
    loadData();
    setupUI();
    setWindowTitle("항공권 예매 시스템 [그래프 자료구조 예제]");
    resize(1100, 640);
}

MainWindow::~MainWindow() { delete graph; }

// 공항 그래프에 노드(공항)와 간선(항공편) 데이터를 직접 코드에 입력하여 등록하는 함수.
// 실제 서비스라면 서버에서 받아오겠지만, 이 프로젝트에서는 서버 구현 없이
// 고정된 값을 코드에 직접 하드코딩하여 사용함.
// addAirport()는 airports[] 배열에 공항 구조체를 순서대로 저장하므로,
// 호출 순서가 곧 인덱스(0~7)가 됨. 이 순서는 MapWidget의 POS[] 배열 순서와 반드시 일치해야 함.
void MainWindow::loadData() {
    graph = new AirportGraph();

    // 공항 추가: 호출 순서 = 인덱스(0~7), MapWidget POS[]와 순서 일치 필수
    graph->addAirport("ICN", "인천국제공항",   "인천/서울");
    graph->addAirport("GMP", "김포국제공항",   "서울");
    graph->addAirport("CJU", "제주국제공항",   "제주");
    graph->addAirport("PUS", "김해국제공항",   "부산");
    graph->addAirport("NRT", "나리타국제공항", "도쿄");
    graph->addAirport("LAX", "LA국제공항",     "로스앤젤레스");
    graph->addAirport("SIN", "창이국제공항",   "싱가포르");
    graph->addAirport("HKG", "홍콩국제공항",   "홍콩");

    // 항공편(간선) 추가: addFlight() 내부에서 adj[src][dst]=true로 간선을 표시하고,
    // flightMap[{src,dst}]에 Flight 객체를 append함 (방향 그래프, 동일 구간에 여러 편 가능)
    // Flight(출발인덱스, 도착인덱스, 편명, 항공사, 출발시간, 도착시간, 가격(원), 소요시간(분))
    // ICN(0) 출발
    graph->addFlight(Flight(0, 2, "DS001", "대한항공",     "08:00", "09:05",  85000,  65));
    graph->addFlight(Flight(0, 2, "DS002", "제주항공",     "09:30", "10:35",  65000,  65));
    graph->addFlight(Flight(0, 3, "DS003", "대한항공",     "07:00", "08:00",  75000,  60));
    graph->addFlight(Flight(0, 3, "DS004", "아시아나항공", "10:00", "11:00",  70000,  60));
    graph->addFlight(Flight(0, 4, "DS005", "대한항공",     "09:00", "11:30", 280000, 150));
    graph->addFlight(Flight(0, 4, "DS006", "아시아나항공", "14:00", "16:30", 260000, 150));
    graph->addFlight(Flight(0, 5, "DS007", "대한항공",     "11:30", "06:30", 980000, 540));
    graph->addFlight(Flight(0, 5, "DS008", "아시아나항공", "09:00", "04:00", 900000, 540));
    graph->addFlight(Flight(0, 6, "DS009", "대한항공",     "13:00", "18:30", 520000, 390));
    graph->addFlight(Flight(0, 6, "DS010", "싱가포르항공", "10:00", "15:30", 490000, 390));
    graph->addFlight(Flight(0, 7, "DS011", "대한항공",     "09:00", "12:00", 380000, 230));
    graph->addFlight(Flight(0, 7, "DS012", "캐세이퍼시픽", "12:00", "15:00", 350000, 230));

    // CJU(2) 출발
    graph->addFlight(Flight(2, 0, "DS013", "대한항공",     "10:00", "11:05",  85000,  65));
    graph->addFlight(Flight(2, 0, "DS014", "제주항공",     "11:30", "12:35",  65000,  65));
    graph->addFlight(Flight(2, 3, "DS015", "대한항공",     "08:00", "08:50",  55000,  50));

    // PUS(3) 출발
    graph->addFlight(Flight(3, 0, "DS016", "대한항공",     "09:00", "10:00",  75000,  60));
    graph->addFlight(Flight(3, 0, "DS017", "아시아나항공", "13:00", "14:00",  70000,  60));
    graph->addFlight(Flight(3, 4, "DS018", "대한항공",     "12:00", "14:30", 250000,  90));

    // NRT(4) 출발
    graph->addFlight(Flight(4, 0, "DS019", "대한항공",     "13:00", "15:30", 280000, 150));
    graph->addFlight(Flight(4, 5, "DS020", "ANA",          "16:30", "08:30", 850000, 540));
    graph->addFlight(Flight(4, 6, "DS021", "싱가포르항공", "17:30", "23:30", 620000, 390));

    // LAX(5) 출발
    graph->addFlight(Flight(5, 0, "DS022", "대한항공",     "11:30", "16:30", 980000, 540));
    graph->addFlight(Flight(5, 4, "DS023", "ANA",          "09:00", "13:30", 850000, 540));

    // SIN(6) 출발
    graph->addFlight(Flight(6, 0, "DS024", "대한항공",     "20:00", "03:30", 520000, 390));
    graph->addFlight(Flight(6, 7, "DS025", "싱가포르항공", "08:00", "10:30", 180000, 150));

    // HKG(7) 출발
    graph->addFlight(Flight(7, 0, "DS026", "대한항공",     "14:00", "19:00", 380000, 230));
    graph->addFlight(Flight(7, 6, "DS027", "캐세이퍼시픽", "09:00", "11:30", 180000, 150));
}

//전체 UI 레이아웃을 구성하는 함수구성.
//QMainWindow의 중앙 위젯(central)에 QHBoxLayout을 설정하여
//왼쪽(MapWidget, stretch=2)과 오른쪽(QFrame 고정 400px)으로 좌우 분할합니다.
//Qt의 시그널-슬롯 메커니즘으로 공항 버튼 클릭과 항공편 리스트 클릭 이벤트를 연결했습니다.
void MainWindow::setupUI() {
    auto* central = new QWidget(this);
    setCentralWidget(central);
    auto* mainLayout = new QHBoxLayout(central);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    //MapWidget(세계지도+공항버튼+노선선)을 stretch=2로 추가해 왼쪽 영역을 넓게 배치
    mapWidget = new MapWidget(graph, central);
    //Qt 시그널-슬롯 연결: MapWidget 내부 QPushButton 클릭 → airportClicked(int) emit
    //→ MainWindow::onAirportClicked(int) 호출로 이어지는 이벤트 체인 구성하였습니다.
    connect(mapWidget, &MapWidget::airportClicked, this, &MainWindow::onAirportClicked);
    mainLayout->addWidget(mapWidget, 2);

    // 오른쪽 패널: QFrame을 400px 고정 너비로 배치하고,
    // 내부에 QVBoxLayout으로 공항명 레이블 → 출발편 섹션 → 도착편 섹션 순서로 쌓았습니다.
    auto* rightFrame = new QFrame(central);
    rightFrame->setStyleSheet("background-color: #0f0f1a; color: white;");
    rightFrame->setFixedWidth(400);
    auto* rightLayout = new QVBoxLayout(rightFrame);
    rightLayout->setContentsMargins(16, 16, 16, 16);
    rightLayout->setSpacing(8);

    // airportNameLabel: 초기값 "공항을 클릭하세요", onAirportClicked()에서 setText()로 갱신되도록 구현하였습니다.
    airportNameLabel = new QLabel("공항을 클릭하세요");
    airportNameLabel->setStyleSheet("color: white; font-size: 18px; font-weight: bold;");
    rightLayout->addWidget(airportNameLabel);

    auto* subLabel = new QLabel("아래 항공편을 클릭하면 예매 성공!");
    subLabel->setStyleSheet("color: #aaa; font-size: 12px;");
    rightLayout->addWidget(subLabel);

    rightLayout->addSpacing(8);

    // 출발편 섹션: QLabel(건수 표시) + QListWidget(항목 목록)으로 구성됩니다.
    // depCountLabel은 onAirportClicked()에서 "%1건" 형식으로 setText() 갱신됩니다.
    depCountLabel = new QLabel("✈ 출발 항공편");
    depCountLabel->setStyleSheet("color: #4CAF50; font-size: 13px; font-weight: bold;");
    rightLayout->addWidget(depCountLabel);

    depList = new QListWidget();
    depList->setStyleSheet(
        "QListWidget { background: #1a1a2e; color: white; border: none; }"
        "QListWidget::item { padding: 6px; border-bottom: 1px solid #333; }"
        "QListWidget::item:hover { background: #2a2a4e; }"
    );
    depList->setMaximumHeight(200);
    rightLayout->addWidget(depList);

    rightLayout->addSpacing(8);

    // 도착편 섹션: QLabel(건수 표시) + QListWidget(항목 목록)으로 구성하였습니다.
    // arrCountLabel은 onAirportClicked()에서 "%1건" 형식으로 setText() 갱신되도록 구현하였습니다.
    arrCountLabel = new QLabel("✈ 도착 항공편");
    arrCountLabel->setStyleSheet("color: #FF9800; font-size: 13px; font-weight: bold;");
    rightLayout->addWidget(arrCountLabel);

    arrList = new QListWidget();
    arrList->setStyleSheet(
        "QListWidget { background: #1a1a2e; color: white; border: none; }"
        "QListWidget::item { padding: 6px; border-bottom: 1px solid #333; }"
        "QListWidget::item:hover { background: #2a2a4e; }"
    );
    arrList->setMaximumHeight(200);
    rightLayout->addWidget(arrList);

    rightLayout->addStretch();
    mainLayout->addWidget(rightFrame);

    //depList와 arrList 둘 다 같은 슬롯(onFlightClicked)에 연결합니다.
    //Qt 시그널-슬롯: QListWidget::itemClicked(QListWidgetItem*) → MainWindow::onFlightClicked
    connect(depList, &QListWidget::itemClicked, this, &MainWindow::onFlightClicked);
    connect(arrList, &QListWidget::itemClicked, this, &MainWindow::onFlightClicked);
}

//공항 버튼 클릭 시 호출되는 슬롯.
//index를 받아 graph->getFlightsFrom/To()로 인접 행렬을 순회해 항공편 목록을 얻고,
//결과를 멤버 변수 depFlights/arrFlights에 저장한 뒤 QListWidget에 문자열로 표시함.
//depFlights/arrFlights를 멤버로 보관하는 이유는 onFlightClicked()에서
//currentRow()로 인덱스를 얻어 해당 Flight 객체에 접근하기 위함.
void MainWindow::onAirportClicked(int index) {
    Airport ap = graph->getAirport(index);
    airportNameLabel->setText(QString("%1 (%2)").arg(ap.city, ap.code));

    //getFlightsFrom/To: 내부적으로 adj[index][j] / adj[j][index]를 순회하여 반환
    depFlights = graph->getFlightsFrom(index);
    arrFlights = graph->getFlightsTo(index);

    depCountLabel->setText(QString("✈ 출발 항공편 (%1건)").arg(depFlights.size()));
    arrCountLabel->setText(QString("✈ 도착 항공편 (%1건)").arg(arrFlights.size()));

    // depFlights를 순회하며 "[편명] 출발→도착,₩가격,N시간 M분"형식으로 addItem
    depList->clear();
    for (const Flight& f : depFlights) {
        Airport dst = graph->getAirport(f.dst);
        depList->addItem(
            QString("[%1] %2 → %3  ·  ₩%4  ·  %5시간 %6분")
                .arg(f.number)
                .arg(ap.code).arg(dst.code)
                .arg(f.price)
                .arg(f.duration / 60).arg(f.duration % 60)
        );
    }

    //arrFlights를 순회하며 동일한 형식으로 addItem
    arrList->clear();
    for (const Flight& f : arrFlights) {
        Airport src = graph->getAirport(f.src);
        arrList->addItem(
            QString("[%1] %2 → %3  ·  ₩%4  ·  %5시간 %6분")
                .arg(f.number)
                .arg(src.code).arg(ap.code)
                .arg(f.price)
                .arg(f.duration / 60).arg(f.duration % 60)
        );
    }
}

//항공편 목록 항목 클릭 시 호출되는 슬롯 (depList/arrList 공통).
//depList와 arrList가 모두 이 슬롯에 연결되어 있으므로,
//currentItem()과 item을 비교하여 클릭이 어느 리스트에서 발생했는지 판별하도록 구현.
//currentRow()로 인덱스를 얻어 depFlights/arrFlights QVector에서 해당 Flight를 꺼내도록 하였습니다.
//QMessageBox::information으로 항공편 번호,항공사,구간,가격,소요시간을 팝업으로 출력하였습니다
void MainWindow::onFlightClicked(QListWidgetItem* item) {
    // depList/arrList 중 어느 쪽에서 클릭됐는지 currentItem()비교로 판별하는 함수.
    bool isDep = (depList->currentItem() == item);
    QVector<Flight>& flights = isDep ? depFlights : arrFlights;
    int row = isDep ? depList->currentRow() : arrList->currentRow();

    if (row < 0 || row >= flights.size()) return;
    const Flight& f = flights[row];  // row 인덱스로 Flight 객체 접근
    Airport src = graph->getAirport(f.src);
    Airport dst = graph->getAirport(f.dst);

    // QMessageBox::information: 모달 팝업으로 예매 완료 정보 출력합니다.
    QMessageBox::information(this, "예매 완료",
        QString("예매가 완료되었습니다.\n\n"
                "항공편: %1  (%2)\n"
                "구간: %3 → %4\n"
                "가격: ₩%5\n"
                "소요시간: %6시간 %7분")
            .arg(f.number).arg(f.airline)
            .arg(src.code).arg(dst.code)
            .arg(f.price)
            .arg(f.duration / 60).arg(f.duration % 60)
    );
}
