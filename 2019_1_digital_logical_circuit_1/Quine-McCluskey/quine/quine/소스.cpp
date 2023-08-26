#include<iostream>//파일 읽기를 위한 헤더파일
#include<fstream>//파일 출력을 위한 헤더파일
using namespace std;//네임스페이스 사용
int main() {
	int forpause = 0;//화면 캡처를 위한 함수
	int num_input = 0;//입력한 값의 수
	int num_care = 0;//Minterm의 갯수
	int num_col2_row=0;//
	int num_final = 0;//Prime Implicants의 갯수
	int dif_num = 0;//문자비교에 사용
	int move_col2 = 1;//column여부 판별
	int num_zero = 0;//0의수
	int num_one = 0;//1의수
	int num_blank = 0;//-의수
	int num_can = 0;//(A'*B')=(A+B)'로의 치환을 위한 변수
	int num_ese=0;//필수주항의 수
	int tr = 0;//트랜지스터의 수
	ifstream fin;//파일 입력
	fin.open("input_minterm.txt");//파일 열기
	ofstream output;//파일 출력
	output.open("result.txt");//파일출력
	char but[1000];
	if (!fin.is_open()) {//파일 존재여부 확인
		cout << "failed file read" << endl;
		cin >> forpause;
		return 0;
	}
	fin.getline(but, sizeof(but));
	int num_bit = 0;//bit수
	for (int i = 0; but[i] != '\0'; i++) {//bit수 계산
		num_bit = (num_bit * 10) + but[i]-'0';
	}
	while (!fin.eof()) {//txt파일 2번째줄부터 끝까지 입력받기
		fin.getline(but, sizeof(but));
		num_input++;
	}
	fin.close();//파일닫기
	//행 수
	int row_size = num_input * num_input / 2 + 1;
	char ** column1 = new char*[row_size];//column1선언(계산되는 값)
	for (int num = 0; num < row_size; num++) {
		column1[num] = new char[num_bit+3];
	}
	for (int k = 0; k < row_size; k++) {
		for (int p = 0; p < num_bit + 2; p++) {
			column1[k][p] = '?';
		}
	}
	char ** column2 = new char*[row_size];//column2선언(계산결과)
	for (int num = 0; num < row_size; num++) {
		column2[num] = new char[num_bit + 3];
	}
	for (int k = 0; k <  row_size; k++) {
		for (int p = 0; p < num_bit + 2; p++) {
			column2[k][p] = '?';
		}
	}
	char ** care = new char*[num_input];//Minterm 선언
	for (int num = 0; num < num_input; num++) {
		care[num] = new char[num_bit];
	}
	char ** final = new char*[row_size];//prime implicants
	for (int num = 0; num < row_size; num++) {
		final[num] = new char[num_bit + 1];
	}
	
	/*for (int k = 0; k < row_size; k++) {
		for (int p = 0; p < num_bit + 2; p++) {
			final[k][p] = '?';
		}
	}*/
	
	fin.open("input_minterm.txt");//파일 다시열어 문자열 받기
	fin.getline(but, sizeof(but));//첫문장 제거
	for (int k = 0; k < num_input; k++) {
		fin.getline(column1[k], (num_bit + 3));
		column1[k][1] = '0';
		column1[k][num_bit + 2]='\0';
	}
	for (int k = num_input; k < row_size; k++) {//쓰레기값 제거
		column1[k][0] = '?';
		column1[k][1] = '?';
		column1[k][num_bit + 2] = '\0';
	}
	for (int num_of_row1 = 0; num_of_row1 < num_input; num_of_row1++) {//1의 개수 확인
		for (int i = 2; i < num_bit + 2; i++) {
			if (column1[num_of_row1][i] == '1') {
				column1[num_of_row1][1]++;
			}
		}
	}
	for (int num_of_row1 = 0; num_of_row1 < num_input; num_of_row1++) {//Minterm넘겨주기
		if (column1[num_of_row1][0] == 'm') {
			for (int num_of_row2 = 2; num_of_row2 < num_bit + 2; num_of_row2++) {
				care[num_care][num_of_row2-2] = column1[num_of_row1][num_of_row2];
			}
			num_care++;
		}
	}
	for (int i = 0; i < num_input; i++) {//변형여부를 확인을 위한 초기화
		column1[i][0] = '0';
	}
	for (int i = 0; i < row_size; i++) {//변형여부를 확인을 위한 초기화
		column2[i][0] = '0';
	}
	
	do{//column1을 column2로 바꿔주며 Pls를 도출하는 반복문
		move_col2 = 0;//움직임여부
		num_col2_row = 0;//column2줄
		for (int num_of_row1 = 0; num_of_row1 < row_size; num_of_row1++) {
			for (int i = num_of_row1 + 1; i < row_size; i++) {
				dif_num = 0;
				if (column1[num_of_row1][1] - column1[i][1] == -1|| column1[num_of_row1][1] - column1[i][1] == 1) {//초기에 1갯수가 1개 차이인지 확인
					for (int j = 2; j < 2 + num_bit; j++) {
						if (column1[num_of_row1][j] == '-') {//-가 2개 한줄에 있지 않는 경우
							if (column1[i][j] != '-') {
								dif_num += 2;//서로간 변형불가
							}
						}
						else if (column1[num_of_row1][j] != column1[i][j]) {//문자 간 다른 갯수
							dif_num++;
						}
					}
				}
				if (dif_num == 1) {//하나만 달라 변형가능
					column1[num_of_row1][0]++;//주항이 아니다
					column1[i][0]++;//주항이 아니다
					if (column1[num_of_row1][1] - column1[i][1] == -1) {//변형을 받는 경우 중
						column2[num_col2_row][1] = column1[num_of_row1][1];
					}
					else if (column1[num_of_row1][1] - column1[i][1] == 1) {//변형을 받는 경우
						column2[num_col2_row][1] = column1[num_of_row1][1]-1;
					}
					for (int j = 2; j < 2 + num_bit; j++) {
						if (column1[num_of_row1][j] != column1[i][j]) {//각 값이 달라 변형 가능한 경우
							column2[num_col2_row][j] = '-';
						}
						else {
							column2[num_col2_row][j] = column1[num_of_row1][j];//값이 같을시 유지
						}
						move_col2=1;//변형이 일어남.
					}
					num_col2_row++;//column2갯수 상승
				}
			}
		}
		//column2생성, 정의
		for (int i = 0; i <row_size; i++) {
			if (column1[i][0] == '0'&&column1[i][1]!='?') {//더이상 변경 불가능한 값을 prime implicants로 옮겨줌.
				for (int j = 2; j < num_bit + 2; j++) {
					final[num_final][j - 2] = column1[i][j];
				}
				num_final++;//갯수 상승
				dif_num = 0;
				for (int j = 0; j < num_bit; j++) {
					if (num_final != 1 && final[num_final - 2][j] != final[num_final-1][j]) {//주항 중복확인
						dif_num++;
						break;
					}
				}
				if (num_final != 1 && dif_num == 0) {//중복시 제거
					for (int j = 0; j < num_bit; j++) {
						final[num_final-1][j] = '?';
					}
					num_final--;
				}
			}
		}
		for (int k = 0; k < row_size; k++) {//column2를 column1로 옮겨준다.
			for (int p = 0; p < num_bit + 2; p++) {
				column1[k][p] = column2[k][p];
			}
		}
		for (int k = 0; k < row_size; k++) {//column2 전체를 ?로 초기화
			for (int p = 0; p < num_bit + 2; p++) {
				column2[k][p]='?';
			}
		}
		for (int i = 0; i < row_size; i++) {//column1의 변형여부를 0으로 초기화
			column1[i][0] = '0';
			column2[i][0] = '0';
		}
	} while (move_col2 == 1);//모든 값이 변형불가능 할때까지 반복
	fin.close();//파일 닫기
	//care출력
	char ** ese_Pls = new char*[num_final+1];//주항차트 선언
	for (int num = 0; num < num_final+1; num++) {
		ese_Pls[num] = new char[num_care];
	}
	int dif_ese = 0;
	for (int i = 0; i < num_care; i++) {//한 열의 X의 수를 표현하는 마지막 줄을 0으로 초기화
		ese_Pls[num_final][i] = '0';
	}
	for (int i = 0; i < num_final; i++) {//주항차트 생성
		for (int j = 0; j < num_care; j++) {
			dif_ese=0;
			for (int k = 0; k<num_bit; k++) {//각 주항과 각 Minterm비교
				if (final[i][k] != '-' && final[i][k] != care[j][k]) {
					dif_ese = 1;
					ese_Pls[i][j] = '0';
					break;
				}
			}
			if (dif_ese == 0) {//비교 결과에 따라 X,O입력
				ese_Pls[i][j] = 'X';
				ese_Pls[num_final][j]++;
			}
		}
	}
	char imsi;
	for (int j = 0; j < num_care; j++) {//열의 X개수가 1일때 같은 행의 X가 포함된 열도 제거 제거
		for (int i = 0; i < num_final; i++) {
			if (ese_Pls[num_final][j] == '1'&&ese_Pls[i][j] == 'X') {//열에서 X갯수가 1임을 확인
				for (int k = 0; k < num_care; k++) {
					if (ese_Pls[i][k] == 'X' && ese_Pls[num_final][k] != 'a') {//해당 열 제거
						ese_Pls[num_final][k] = 'a';
					}
				}
				for (int l = 0; l < num_bit; l++) {//주항의 요소 확인
					imsi = final[i][l];
					output << imsi;
					if (final[i][l] == '0') {//0의 수
						num_zero++;
					}
					else if (final[i][l] == '-') {//-의 수
						num_blank++;
					}
					else if (final[i][l] == '1') {//1의 수
						num_one++;
					}
				}
				if (num_bit == num_blank) {//모든 항이 blank일경우 코드종료
					tr = 0;
					output << tr;
					cin>> forpause;
					return 0;
				}
				else if (num_bit == num_blank + 1) {//0 혹은 1이 1개일 경우
					if (num_zero == 1) {//0일경우 inverter에 의해 2추가
						tr += 2;
						num_can++;
					}
				}
				else if (num_bit - num_blank > 1) {//0혹은 1이 2개이상일 경우
					tr += (num_bit - num_blank + 1) * 2;//input갯수에 따른 트랜지스터값 상승
					if (num_zero - num_one > 0) {//0이 더 많을시 (A'*B')=(A+B)'로 치환해 트랜지스터 개수 감소
						num_can++;
						tr += (num_one + 1) * 2;
					}
					else {
						tr += num_zero * 2;
					}
				}
				num_zero = 0;//0의 수 초기화
				num_one = 0;//1의 수 초기화
				num_blank = 0;//-의 수 초기화
				tr += 2;//기본적으로 사용되는 tr
				num_ese++;
				output << endl;
			}
		}
	}
	for (int j = 0; j <num_care; j++) {//열의 X개수가 1 이상일때 같은 행의 X가 포함된 열도 제거 제거
		for (int i = num_final-1; i >=0; i--) {//X와 -가 많은 아래부터 계산
			if (ese_Pls[num_final][j] != 'a'&&ese_Pls[i][j] == 'X') {//위에서 계산하지 않은 열 판단
				for (int k = 0; k < num_care; k++) {//해당열제거
					if (ese_Pls[i][k] == 'X' && ese_Pls[num_final][k] != 'a') {
						ese_Pls[num_final][k] = 'a';
					}
				}
				for (int l = 0; l < num_bit; l++) {
					output << final[i][l];//파일에 입력
					if (final[i][l] == '0') {//0의수 증가
						num_zero++;
					}
					else if (final[i][l] == '-') {//-의 수 증가
						num_blank++;
					}
					else if (final[i][l] == '1') {//1의 수 증가
						num_one++;
					}
				}
				if (num_bit == num_blank) {//모든 항이 blank일경우 코드종료 
					tr = 0;
					output << "Cost(# of transistors) : " << tr;
					output.close();
					cin >> forpause;
					return 0;
				}
				else if (num_bit == num_blank + 1){//0 혹은 1이 1개일 경우
					if (num_zero == 1) {//0일경우 inverter에 의해 2추가
						tr += 2;
						num_can++;
					}
				}
				else if (num_bit - num_blank > 1) {//0혹은 1이 2개이상일 경우
					tr += (num_bit - num_blank + 1) * 2;//input갯수에 따른 트랜지스터값 상승
					if (num_zero - num_one > 0) {//0이 더 많을시 (A'*B')=(A+B)'로 치환해 트랜지스터 개수 감소
						num_can++;
						tr += (num_one + 1) * 2;
					}
					else {
						tr += num_zero * 2;
					}
				}
				num_zero = 0;//0의 수 초기화
				num_one = 0;//1의 수 초기화
				num_blank = 0;//-의 수 초기화
				tr += 2;
				output << endl;
				num_ese++;
				break;
			}
		}
	}
	
	tr += 2;//기본 추가 트랜지스터 갯수
	if (num_ese==1) {//사용 주항이 1개일 경우
		tr -= 4;
	}
	if (num_can>1) {//(A'*B')=(A+B)'로 치환해 트랜지스터 개수 감소
		tr -= (num_can - 1) * 2;
	}
	
	output << endl<<"Cost(# of transistors) : " <<tr;//트랜지스터의 갯수를 파일 입력
	num_zero = 0;//0의 수 초기화
	num_one = 0;//1의 수 초기화
	num_blank = 0;//-의 수 초기화
	for (int y = 0; y < row_size; y++) {
		delete[] final[y];
	}
	for (int y = 0; y < num_final+1; y++) { //동적할당해준 2차원배열들의 해체
		delete[] ese_Pls[y];
	}
	for (int y = 0; y < row_size; y++) {
		delete[] column1[y];
	}
	for (int y = 0; y < row_size; y++) {
		delete[] column2[y];
	}
	for (int y = 0; y < num_input; y++) {
		delete[] care[y];
	}
	delete[] ese_Pls;
	delete[] column1;
	delete[] column2;
	delete[] care;
	delete[] final;
	output.close();//파일 종료
	cin >> forpause;
	return 0;
}