#include "manager.h"

Manager::Manager() {
}
Manager::~Manager() {
	studentScores->clear();
	delete menu;
}

// 성적처리프로그램 매니저 클래스 세팅
void Manager::Init() {
	studentScores = new SMap<StudentScore*>();
	menu = new Menu();
	menu->Init();
}

// 실행
void Manager::Run() {
	while (true)
	{
		// 메인 메뉴 선택
		String* select = menu->MainMenu();

		if (*select == "1")
		{
			CreateScore();
		}
		else if (*select == "2") 
		{
			SearchScore();
		}
		else if (*select == "3")
		{
			PrintScore();
		}
		else if (*select == "4") 
		{
			break;
		}
	}

	return;
}

// 전체 성적 출력 함수
// 저장된 모든 성적을 출력합니다.
void Manager::PrintScore() { 

	if (studentScores->count <= 0)
	{
		cout << "저장된 정보가 없습니다." << endl;
	}
	else {
		system("cls");
		cout << "학생 성적 출력" << endl << endl;

		for (int i = 0; i < studentScores->count; i++)
		{
			// 현재 점수 목록에서 Key 값을 통해 값 획득
			StudentScore* student = studentScores->GetValueByKey(studentScores->keys.elementAt(i));
			student->PrintScore(menu);
		}
	}

	system("PAUSE");
}

// 성적 신규 추가 로직
void Manager::CreateScore() {
	while (true)
	{
		// 학과 메뉴 선택
		String departmentType = menu->DepartmentMenu();

		// 잘못된 학과 선택시 빈 문자열 반환 - 루프처리기 때분에 DepartmentMenu() 내부에 구현하기엔 부담
		if (strcmp(departmentType.characters, "") == 0)
		{
			cout << "학과를 다시 선택해 주세요." << endl;
			continue;
		}

		// 해당 학과의 과목정보 로드
		List<String>* subjects = menu->classMenu[departmentType.characters];


		system("cls");
		cout << "학생정보 입력" << endl << endl;

		String inputName, inputUid, inputScore;

		while (true)
		{
			cout << "학번: ";
			cin >> inputUid;

			// 입력된 학번에 대한 중복 검사
			if (studentScores->ContainKey(inputUid.characters))
			{
				cout << "이미 사용중인 학번. 다시 입력" << endl;
				inputUid = "";
				continue;
			}
			else break;
		}

		cout << "이름: ";
		cin >> inputName;

		// 입력받은 값을 통해 신규 학생점수 클래스 생성
		// 점수 또한 따로 입력 받은 후, 마지막에 생성하는 형태가 더 좋을것 같다고 생각
		StudentScore* student = new StudentScore(inputName, inputUid, departmentType.characters);

		cout << endl << "학생점수 입력" << endl << endl;

		for (int i = 0; i < subjects->count; i++) 
		{
			cout << subjects->elementAt(i) << ": ";
			cin >> inputScore;

			// 점수 범위검사 추가 로직 필요
			
			student->setScore(i, atoi(inputScore.characters));
		}

		// 생성된 신규 점수 추가
		studentScores->add(student->getUid().characters, student);
		break;
	}
}


// 점수 검색 로직
// 입력한 학번과 일치하는 점수만 출력 - 출력되는 점수는 항상 1개
void Manager::SearchScore() {
	system("cls");
	cout << "학생점수 검색" << endl << endl;

	String input;

	cout << "학번 입력: ";
	cin >> input;

	// 저장된 점수목록에 입력값이 있는지 확인 
	if (!studentScores->ContainKey(input.characters)) {
		cout << "학번을 찾을 수 없습니다.";
	}
	else 
	{
		system("cls");
		cout << "학생 성적 조회 결과" << endl << endl;

		// 해당 점수 출력
		StudentScore* student = studentScores->GetValueByKey(input.characters);
		student->PrintScore(menu);
	}

	system("PAUSE");
}


