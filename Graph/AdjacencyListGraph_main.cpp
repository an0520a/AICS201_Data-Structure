#include <iostream>
#include <string>
#include "AdjacencyListGraph.hpp"
#include "AdjacencyListGraph.cpp"

using namespace std;

int main()
{
    AL_Graph<const char *, int> station;

    station.insertVertex("서울역");
    station.insertVertex("오송역");
    station.insertVertex("대전역");
    station.insertVertex("동대구역");
    station.insertVertex("부산역");
    station.insertVertex("광주역");
    station.insertVertex("목포역");

    Vector<AL_Graph<const char *, int>::Vertex> VertList = station.getVertices();

    AL_Graph<const char *, int>::Vertex Seoul = VertList[0];
    AL_Graph<const char *, int>::Vertex Osong = VertList[1];
    AL_Graph<const char *, int>::Vertex Daejeon = VertList[2];
    AL_Graph<const char *, int>::Vertex Dongdaegu = VertList[3];
    AL_Graph<const char *, int>::Vertex Busan = VertList[4];
    AL_Graph<const char *, int>::Vertex Gwangju = VertList[5];
    AL_Graph<const char *, int>::Vertex Mokpo = VertList[6];

    station.insertEdge(Seoul, Osong, 110);
    station.insertEdge(Osong, Seoul, 110);
    station.insertEdge(Osong, Daejeon, 30);
    station.insertEdge(Daejeon, Osong, 30);
    station.insertEdge(Daejeon, Dongdaegu, 120);
    station.insertEdge(Dongdaegu, Daejeon, 120);
    station.insertEdge(Dongdaegu, Busan, 90);
    station.insertEdge(Busan, Dongdaegu, 90);
    station.insertEdge(Osong, Gwangju, 100);
    station.insertEdge(Gwangju, Mokpo, 100);

    cout << "DFS TEST, 예상출력 : 서울역 오송역 대전역 동대구역 부산역 광주역 목포역" << endl;
    cout << "DFS TEST, 실제출력 : ";
    Vector<AL_Graph<const char *, int>::Vertex> DFS_TEST = station.DFS(Seoul);
    for (int i = 0; i < DFS_TEST.size(); i++)
    {
        cout << *DFS_TEST[i] << ' ';
    }
    cout << "\n\n";

    cout << "BFS TEST, 예상출력 : 서울역 오송역 대전역 광주역 동대구역 목포역 부산역" << endl;
    cout << "BFS TEST, 실제출력 : ";
    Vector<AL_Graph<const char *, int>::Vertex> BFS_TEST = station.BFS(Seoul);
    for (int i = 0; i < DFS_TEST.size(); i++)
    {
        cout << *BFS_TEST[i] << ' ';
    }
    cout << "\n\n";

    AL_Graph<const char *, int>::Edge Seoul_Osong = station.getEdge(Seoul, Osong);

    station.Dijkstra(Seoul);

    station.insertVertex("천안역");
    station.insertVertex("수원역");
    VertList.clear();
    VertList = station.getVertices();

    AL_Graph<const char *, int>::Vertex Cheonan = VertList[7];
    AL_Graph<const char *, int>::Vertex Suwon = VertList[8];

    station.eraseEdge(Seoul_Osong);

    station.insertEdge(Seoul, Cheonan, 40);
    station.insertEdge(Cheonan, Seoul, 40);
    station.insertEdge(Cheonan, Osong, 70);
    station.insertEdge(Osong, Cheonan, 70);
    station.insertEdge(Cheonan, Suwon, 100);
    station.insertEdge(Suwon, Cheonan, 100);
    station.insertEdge(Suwon, Osong, 20);
    station.insertEdge(Osong, Suwon, 20);

    cout << '\n';

    station.Dijkstra(Seoul);

    //station.eraseEdge(Seoul_Osong);

    /*

    cout << "eraseEdge(seoul->osong) TEST, 예상출력 : 서울역" << endl;
    cout << "eraseEdge(seoul->osong) TEST, 실제출력 : ";
    for (int i = 0; i < DFS_TEST.size(); i++)
    {
        cout << *DFS_TEST[i] << ' ';
    }

    cout << "\n\n";

    station.eraseVertex(Dongdaegu);

    DFS_TEST = station.DFS(Osong);

    cout << "eraseVertex(Daejeon) TEST, 예상출력 : 오송역 서울역 대전역 목포역" << endl;
    cout << "eraseVertex(Daejeon) TEST, 실제출력 : ";
    for (int i = 0; i < DFS_TEST.size(); i++)
    {
        cout << *DFS_TEST[i] << ' ';
    }
    cout << "\n\n";
    */
}