//
//  SampleCode.hpp
//

#ifndef SampleCode_hpp
#define SampleCode_hpp

#include <stdio.h>
#include <string>
#include <vector>


#define UNCOPYABLE(classname)      private: classname(const classname&) {};  \
                                            void operator=(const classname&) {};

#define DECLARE_SINGLETONE( classname ) UNCOPYABLE(classname)                           \
                                        public:                                         \
                                                static classname& getInstance()         \
                                                { static classname instance; return instance; } \
                                        private:
enum BOOST_TARGET
{
    BOOST_TARGET_NONE = 0,
    BOOST_TARGET_FIELD = 1,   // 밭
    BOOST_TARGET_TREE = 2,    // 나무
    BOOST_TARGET_ANIMAL = 3,  // 가축
    BOOST_TARGET_FACTORY = 4, // 공장
};

enum BOOST_TYPE
{
    BOOST_TYPE_NONE = 0,
    BOOST_TYPE_QUANTITY = 1,    // 수량을 증가
    BOOST_TYPE_TIME = 2,        // 시간을 단축
};

/*
* 부스트 효과 정보
*/
struct BoostData {

    int _boostNumber;           // 효과번호
    float _boostValue;          // 효과 적용치
    BOOST_TARGET _boostTarget;  // 효과 종류
    BOOST_TYPE _boostType;      // 효과 타입
    std::string _description;

    std::vector<std::tuple<int, int, int>> _vNeedItem;  // 필요 아이템 ( 번호, 타입, 수량 )

    BoostData()
    {
        _boostNumber = -1;
        _boostValue = -1;
        _boostTarget = BOOST_TARGET_NONE;
        _boostType = BOOST_TYPE_NONE;
        _description = "";

        _vNeedItem.clear();
    }
};

typedef std::vector< const BoostData* > ListBoostData;

/*
 * 서버에서 받아온 적용중인 부스트 정보
 */
struct BoostTaskData {

    int _boostNumber;           // 효과번호
    int _boostSlotNumber;       // 효과 슬롯번호
    long long _startTime;       // 버프 적용 시작시간.
    long long _endTime;         // 버프 적용 종료시간.
    
    BoostTaskData()
    {
        _boostNumber = -1;
        _boostSlotNumber = -1;
        _startTime = -1;
        _endTime = -1;
    }
};

typedef std::vector< const BoostTaskData* > ListBoostTaskData;

/*
* 부스팅 효과 관리 매니저 클래스
*/
class BoostManager
{
    DECLARE_SINGLETONE(BoostManager);

    BoostManager();
    ~BoostManager();

private:
    void initBoostData();

public:

    const BoostData* getBoostDataByNumber(int _number);
    ListBoostData getAllBoostDataList();

    void removeAllBoostTaskData();

    void setBoostTaskData(BoostTaskData* _pData);
    const BoostTaskData* getBoostTaskData(int _number);

    ListBoostTaskData getBoostTaskDataList();
    ListBoostTaskData getOnEffectiveBoostTaskList();
    bool checkAbleToBoostByNumber(int _number);

private:

    ListBoostData _listBoostData;           // plist data
    ListBoostTaskData _listBoostTaskData;   // server data
};

#define BoostMng BoostManager::getInstance()


#endif /* SampleCode_hpp */
