#include <iostream>
#include "Graph.h"

#define MAX 100

Graph::Graph()
	:
	time( 0 ),
	isEdgeAdded( false )
{
	for( int i = 0; i < 100; ++i )
	{
		discoverTime[i] = 0;
	}
	for( int i = 0; i < 100; ++i )
	{
		visited[i] = false;
	}
}

Graph::Graph( const int& nVertices )
	:
	time( 0 ),
	isEdgeAdded( false )
{
	// 꼭짓점 벡터 초기화
	for( int i = 0; i < nVertices; ++i )
	{
		vertices.emplace_back( i );
	}
	// 간선 벡터 초기화
	edges.resize( nVertices );
	// 단절선 벡터 초기화
	bridges.resize( nVertices );
	// 발견 시간 배열 초기화
	for( int i = 0; i < 100; ++i )
	{
		discoverTime[i] = 0;
	}
	for( int i = 0; i < 100; ++i )
	{
		visited[i] = false;
	}
}

bool Graph::SetConnection( const int& v1, const int& v2 )
{
	if( vertices.size() - 1 < v1 || v1 < 0
	 || vertices.size() - 1 < v2 || v2 < 0 )
	{
		std::cout << "잘못된 꼭짓점을 입력하였습니다." << std::endl;
		return false;
	}

	for( int i = 0; i < edges[v1].size(); ++i )
	{
		if( edges[v1][i] == v2 )
		{
			std::cout << "이미 연결된 정점 입니다." << std::endl;
			return false;
		}
	}
	isEdgeAdded = true;
	edges[v1].emplace_back( v2 );
	edges[v2].emplace_back( v1 );
	return true;
}

void Graph::ShowConnections()
{
	for( int i = 0; i < edges.size(); ++i )
	{
		std::cout << i << " : ";
		for( int j = 0; j < edges[i].size(); ++j )
		{
			std::cout << edges[i][j] << ' ';
		}
		std::cout << std::endl;
	}
}

void Graph::MakeTimeTable()
{
	// 간선이 새로 추가 되었을 때만 발견 시간 테이블을 새로 작성한다.
	if( !isEdgeAdded ) return;

	// 이전에 사용했을 경우를 대비해 discoverTime 배열 및 time을 다시 한 번 초기화.
	time = 0;
	for( int i = 0; i < vertices.size(); ++i )
	{
		discoverTime[i] = 0;
	}

	if( vertices.size() > 0 )
	{
		DfsForTimeTable( 0 );
		isEdgeAdded = false;
	}
	else return;
}

void Graph::DfsForTimeTable( const int& index )
{
	discoverTime[index] = ++time;
	for( int i = 0; i < edges[index].size(); ++i )
	{
		if( !discoverTime[edges[index][i]] )
		{
			DfsForTimeTable( edges[index][i] );
		}
	}
	return;
}

void Graph::ShowBridges()
{
	SearchBridges();
	for( int i = 0; i < bridges.size(); ++i )
	{
		if( bridges[i].size() > 0 )
		{
			for( int j = 0; j < bridges[i].size(); ++j )
			{
				std::cout << i << " - " << bridges[i][j] << ' ';
			}
			std::cout << std::endl;
		}
	}
}

void Graph::PushBridge( const int& from, const int& to )
{
	for( int i = 0; i < bridges[to].size(); ++i )
	{
		if( bridges[to][i] == from ) return;
	}
	bridges[to].emplace_back( from );
}

void Graph::SearchBridges()
{
	bool tmpVisited[MAX];
	
	for( int i = 0; i < vertices.size(); ++i )
	{
		tmpVisited[i] = false;
	}
	
	for( int i = 0; i < edges.size(); ++i )
	{
		tmpVisited[i] = true;
		for( int j = 0; j < edges[i].size(); ++j )
		{
			if( !tmpVisited[edges[i][j]] )
			{
				IsBridge( i, edges[i][j] );
			}
		}
	}
}

/*
	이전에 만든 발견 시간 테이블을 참고하여 브릿지 여부를 판단함.
	처음 매개변수로 주어진 노드 연결에서 from(자식 노드)이(가) 자신과 연결된
	노드들의 발견 시간을 DFS를 통해 탐색함. (이 때, to로 주어진 부모 노드는 제외)
	이렇게 탐색하여 최종 발견 시간(자신과 연결된 노드의 발견 시간 중 최소 값)이
	제일 처음 매개변수로 주어진 to 노드의 발견 시간보다 작거나 같으면, 해당 노드는
	우회로가 존재한다는 것이고, 브릿지가 아니게 된다.
*/
int Graph::DfsForBridge( const int& from, const int& to )
{
	int result = discoverTime[from];
	visited[from] = true;
	for( int i = 0; i < edges[from].size(); ++i )
	{
		int next = edges[from][i];
		if( next == to ) continue;
		if( !visited[next] )
		{
			/*
				매개변수로 주어진 연결 노드를 제외하고 자신과 연결된 노드 중
				발견 시간이 가장 빠른 노드의 발견 시간을 결과 값으로 함. 
			*/
			int before = DfsForBridge( next, from );
			result = result < before ? result : before;
		}
		else
		{
			/*
				다음번 방문할 노드(매개변수로 주어진 연결 노드 제외)가 이미 방문되었을 경우
				자기 자신의 발견 시간 보다 빠르면 해당 값으로 결과값 변경.
			*/
			result = result < discoverTime[next] ? result : discoverTime[next];
		}

	}
	return result;
}

bool Graph::IsBridge( const int& v1, const int& v2 )
{
	// 발견 시간 테이블 설정
	MakeTimeTable();
	// visited 배열이 이전 호출에서 값이 변경되므로 초기화
	for(int i = 0; i < vertices.size(); ++i)
	{
		visited[i] = false;
	}
	/*
		자식 노드에서 시작하여 부모 노드 제외한 나머지 간선을 통해
		더 적은 발견 시간을 갖는 노드로 갈 수 있는지 조사
		자식 노드가 더 긴 발견 시간을 가지므로 from = 자식노드, to = 부모노드
	*/
	int from = 0, to = 0, check = 0;
	if( discoverTime[v1] < discoverTime[v2] )
	{
		to = v1;
		from = v2;
	}
	else
	{
		to = v2;
		from = v1;
	}
	check = DfsForBridge( from, to );
	if( check > discoverTime[to] )
	{
		PushBridge( from, to );
		return true;
	}
	else return false;
}

