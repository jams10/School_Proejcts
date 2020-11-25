#pragma once

#include <vector>

#define MAX 100

class Graph
{
public:
	int time;					// 발견 시간 테이블을 값 할당을 위한 시간 변수
	std::vector<int> vertices;  // 정점 벡터
	std::vector<std::vector<int>> edges;   // 간선 벡터
	std::vector<std::vector<int>> bridges; // 단절선 벡터
	int discoverTime[MAX];                 // 발견 시간 테이블
	bool visited[MAX];                     // DFS에서 사용하는 방문 여부 값 배열
	bool isEdgeAdded;					   // 간선이 새로 추가되었는지 확인하는 변수
public:
	Graph();
	Graph( const int& nVertices );
	// 정점 연결 함수
	bool SetConnection( const int& v1, const int& v2 );
	// 정점 연결 리스트 출력 함수
	void ShowConnections();
	// 발견 시간 테이블 생성 함수(DFS 함수 호출)
	void MakeTimeTable();
	// 전체 단절선 출력 함수
	void ShowBridges();
	// 단절선 추가 함수
	void PushBridge(const int& from, const int& to);
	// 전체 단절선 탐색 함수
	void SearchBridges();
	// 발견 시간 테이블 생성 함수(DFS를 통한 발견 시간 테이블 값 세팅)
	void DfsForTimeTable( const int& index );
	// 브릿지 판별 함수(DFS를 통해 발견 시간 비교)
	int DfsForBridge( const int& from, const int& to );
	// 브릿지 판별 함수(DFS 함수 호출)
	bool IsBridge( const int& v1, const int& v2 );
};
