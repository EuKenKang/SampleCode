//
//  SampleCode.cpp
//

#include "SampleCode.hpp"

BoostManager::BoostManager()
{
    initBoostData();
}

BoostManager::~BoostManager()
{
    for (ListBoostData::iterator itr = _listBoostData.begin(); itr != _listBoostData.end(); ++itr)
        delete (*itr);

    _listBoostData.clear();
}

#pragma mark -
#pragma mark [ plist parsing ]

/*
* 데이터 파싱후 매니저에 로드.
*/
void BoostManager::initBoostData()
{
    
}

#pragma mark -
#pragma mark [ 부스트 고유정보들 ]

/*
* 부스트 버프 고유번호로 정보 반환
*/
const BoostData* BoostManager::getBoostDataByNumber(int _number)
{
    for (auto _data : _listBoostData)
    {
        if (_data->_boostNumber == _number)
            return _data;
    }

    return nullptr;
}

/*
* 모든 부스트 버프 리스트 반환
*/
ListBoostData BoostManager::getAllBoostDataList()
{
    return _listBoostData;
}


#pragma mark -
#pragma mark [ 적용중인 부스트 정보들 ]

/*
* 적용중인 부스트 버프 정보 새로 동기화 전 이전 데이터 모두 제거
*/
void BoostManager::removeAllBoostTaskData()
{
    for (int i = 0; i < _listBoostTaskData.size(); i++)
    {
        const BoostTaskData* _data = _listBoostTaskData.at(i);
        if (_data)
            delete _data;
    }

    _listBoostTaskData.clear();
}

/*
* 서버 콜백 받은후 리스트 세팅
*/
void BoostManager::setBoostTaskData(BoostTaskData* _pData)
{
    _listBoostTaskData.push_back(_pData);
}

/*
* 부스트 고유번호로 적용중인 버프 정보 반환
*/
const BoostTaskData* BoostManager::getBoostTaskData(int _number)
{
    for (auto _data : _listBoostTaskData)
    {
        if (_data->_boostNumber == _number)
            return _data;
    }

    return nullptr;
}

/*
* 모든 버프 리스트 반환
*/
ListBoostTaskData BoostManager::getBoostTaskDataList()
{
    return _listBoostTaskData;
}

/*
* 현재 효과가 적용중인 버프 리스트 반환
*/
ListBoostTaskData BoostManager::getOnEffectiveBoostTaskList()
{
    ListBoostTaskData _result;
    _result.clear();

    for (auto _data : _listBoostTaskData)
    {
        long long _currentTime;                 // 게임 서버에서 받아온 현재시간
        long long _endTime = _data->_endTime;   // 게임 서버에서 받아온 버프 종료시간
        long long _remainTime = _endTime - _currentTime;

        if (_remainTime > 0)
        {
            _result.push_back(_data);
        }
    }

    return _result;
}

/*
* 해당 번호의 부스트효과가 다 소진되었는지 체크
*/
bool BoostManager::checkAbleToBoostByNumber(int _number)
{
    for (auto _data : _listBoostTaskData)
    {
        long long _currentTime;
        long long _endTime = _data->_endTime;
        long long _remainTime = _endTime - _currentTime;

        if (_remainTime > 0)
        {
            return false;
        }
    }

    return true;
}

