#include<iostream>//���� �б⸦ ���� �������
#include<fstream>//���� ����� ���� �������
using namespace std;//���ӽ����̽� ���
int main() {
	int forpause = 0;//ȭ�� ĸó�� ���� �Լ�
	int num_input = 0;//�Է��� ���� ��
	int num_care = 0;//Minterm�� ����
	int num_col2_row=0;//
	int num_final = 0;//Prime Implicants�� ����
	int dif_num = 0;//���ں񱳿� ���
	int move_col2 = 1;//column���� �Ǻ�
	int num_zero = 0;//0�Ǽ�
	int num_one = 0;//1�Ǽ�
	int num_blank = 0;//-�Ǽ�
	int num_can = 0;//(A'*B')=(A+B)'���� ġȯ�� ���� ����
	int num_ese=0;//�ʼ������� ��
	int tr = 0;//Ʈ���������� ��
	ifstream fin;//���� �Է�
	fin.open("input_minterm.txt");//���� ����
	ofstream output;//���� ���
	output.open("result.txt");//�������
	char but[1000];
	if (!fin.is_open()) {//���� ���翩�� Ȯ��
		cout << "failed file read" << endl;
		cin >> forpause;
		return 0;
	}
	fin.getline(but, sizeof(but));
	int num_bit = 0;//bit��
	for (int i = 0; but[i] != '\0'; i++) {//bit�� ���
		num_bit = (num_bit * 10) + but[i]-'0';
	}
	while (!fin.eof()) {//txt���� 2��°�ٺ��� ������ �Է¹ޱ�
		fin.getline(but, sizeof(but));
		num_input++;
	}
	fin.close();//���ϴݱ�
	//�� ��
	int row_size = num_input * num_input / 2 + 1;
	char ** column1 = new char*[row_size];//column1����(���Ǵ� ��)
	for (int num = 0; num < row_size; num++) {
		column1[num] = new char[num_bit+3];
	}
	for (int k = 0; k < row_size; k++) {
		for (int p = 0; p < num_bit + 2; p++) {
			column1[k][p] = '?';
		}
	}
	char ** column2 = new char*[row_size];//column2����(�����)
	for (int num = 0; num < row_size; num++) {
		column2[num] = new char[num_bit + 3];
	}
	for (int k = 0; k <  row_size; k++) {
		for (int p = 0; p < num_bit + 2; p++) {
			column2[k][p] = '?';
		}
	}
	char ** care = new char*[num_input];//Minterm ����
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
	
	fin.open("input_minterm.txt");//���� �ٽÿ��� ���ڿ� �ޱ�
	fin.getline(but, sizeof(but));//ù���� ����
	for (int k = 0; k < num_input; k++) {
		fin.getline(column1[k], (num_bit + 3));
		column1[k][1] = '0';
		column1[k][num_bit + 2]='\0';
	}
	for (int k = num_input; k < row_size; k++) {//�����Ⱚ ����
		column1[k][0] = '?';
		column1[k][1] = '?';
		column1[k][num_bit + 2] = '\0';
	}
	for (int num_of_row1 = 0; num_of_row1 < num_input; num_of_row1++) {//1�� ���� Ȯ��
		for (int i = 2; i < num_bit + 2; i++) {
			if (column1[num_of_row1][i] == '1') {
				column1[num_of_row1][1]++;
			}
		}
	}
	for (int num_of_row1 = 0; num_of_row1 < num_input; num_of_row1++) {//Minterm�Ѱ��ֱ�
		if (column1[num_of_row1][0] == 'm') {
			for (int num_of_row2 = 2; num_of_row2 < num_bit + 2; num_of_row2++) {
				care[num_care][num_of_row2-2] = column1[num_of_row1][num_of_row2];
			}
			num_care++;
		}
	}
	for (int i = 0; i < num_input; i++) {//�������θ� Ȯ���� ���� �ʱ�ȭ
		column1[i][0] = '0';
	}
	for (int i = 0; i < row_size; i++) {//�������θ� Ȯ���� ���� �ʱ�ȭ
		column2[i][0] = '0';
	}
	
	do{//column1�� column2�� �ٲ��ָ� Pls�� �����ϴ� �ݺ���
		move_col2 = 0;//�����ӿ���
		num_col2_row = 0;//column2��
		for (int num_of_row1 = 0; num_of_row1 < row_size; num_of_row1++) {
			for (int i = num_of_row1 + 1; i < row_size; i++) {
				dif_num = 0;
				if (column1[num_of_row1][1] - column1[i][1] == -1|| column1[num_of_row1][1] - column1[i][1] == 1) {//�ʱ⿡ 1������ 1�� �������� Ȯ��
					for (int j = 2; j < 2 + num_bit; j++) {
						if (column1[num_of_row1][j] == '-') {//-�� 2�� ���ٿ� ���� �ʴ� ���
							if (column1[i][j] != '-') {
								dif_num += 2;//���ΰ� �����Ұ�
							}
						}
						else if (column1[num_of_row1][j] != column1[i][j]) {//���� �� �ٸ� ����
							dif_num++;
						}
					}
				}
				if (dif_num == 1) {//�ϳ��� �޶� ��������
					column1[num_of_row1][0]++;//������ �ƴϴ�
					column1[i][0]++;//������ �ƴϴ�
					if (column1[num_of_row1][1] - column1[i][1] == -1) {//������ �޴� ��� ��
						column2[num_col2_row][1] = column1[num_of_row1][1];
					}
					else if (column1[num_of_row1][1] - column1[i][1] == 1) {//������ �޴� ���
						column2[num_col2_row][1] = column1[num_of_row1][1]-1;
					}
					for (int j = 2; j < 2 + num_bit; j++) {
						if (column1[num_of_row1][j] != column1[i][j]) {//�� ���� �޶� ���� ������ ���
							column2[num_col2_row][j] = '-';
						}
						else {
							column2[num_col2_row][j] = column1[num_of_row1][j];//���� ������ ����
						}
						move_col2=1;//������ �Ͼ.
					}
					num_col2_row++;//column2���� ���
				}
			}
		}
		//column2����, ����
		for (int i = 0; i <row_size; i++) {
			if (column1[i][0] == '0'&&column1[i][1]!='?') {//���̻� ���� �Ұ����� ���� prime implicants�� �Ű���.
				for (int j = 2; j < num_bit + 2; j++) {
					final[num_final][j - 2] = column1[i][j];
				}
				num_final++;//���� ���
				dif_num = 0;
				for (int j = 0; j < num_bit; j++) {
					if (num_final != 1 && final[num_final - 2][j] != final[num_final-1][j]) {//���� �ߺ�Ȯ��
						dif_num++;
						break;
					}
				}
				if (num_final != 1 && dif_num == 0) {//�ߺ��� ����
					for (int j = 0; j < num_bit; j++) {
						final[num_final-1][j] = '?';
					}
					num_final--;
				}
			}
		}
		for (int k = 0; k < row_size; k++) {//column2�� column1�� �Ű��ش�.
			for (int p = 0; p < num_bit + 2; p++) {
				column1[k][p] = column2[k][p];
			}
		}
		for (int k = 0; k < row_size; k++) {//column2 ��ü�� ?�� �ʱ�ȭ
			for (int p = 0; p < num_bit + 2; p++) {
				column2[k][p]='?';
			}
		}
		for (int i = 0; i < row_size; i++) {//column1�� �������θ� 0���� �ʱ�ȭ
			column1[i][0] = '0';
			column2[i][0] = '0';
		}
	} while (move_col2 == 1);//��� ���� �����Ұ��� �Ҷ����� �ݺ�
	fin.close();//���� �ݱ�
	//care���
	char ** ese_Pls = new char*[num_final+1];//������Ʈ ����
	for (int num = 0; num < num_final+1; num++) {
		ese_Pls[num] = new char[num_care];
	}
	int dif_ese = 0;
	for (int i = 0; i < num_care; i++) {//�� ���� X�� ���� ǥ���ϴ� ������ ���� 0���� �ʱ�ȭ
		ese_Pls[num_final][i] = '0';
	}
	for (int i = 0; i < num_final; i++) {//������Ʈ ����
		for (int j = 0; j < num_care; j++) {
			dif_ese=0;
			for (int k = 0; k<num_bit; k++) {//�� ���װ� �� Minterm��
				if (final[i][k] != '-' && final[i][k] != care[j][k]) {
					dif_ese = 1;
					ese_Pls[i][j] = '0';
					break;
				}
			}
			if (dif_ese == 0) {//�� ����� ���� X,O�Է�
				ese_Pls[i][j] = 'X';
				ese_Pls[num_final][j]++;
			}
		}
	}
	char imsi;
	for (int j = 0; j < num_care; j++) {//���� X������ 1�϶� ���� ���� X�� ���Ե� ���� ���� ����
		for (int i = 0; i < num_final; i++) {
			if (ese_Pls[num_final][j] == '1'&&ese_Pls[i][j] == 'X') {//������ X������ 1���� Ȯ��
				for (int k = 0; k < num_care; k++) {
					if (ese_Pls[i][k] == 'X' && ese_Pls[num_final][k] != 'a') {//�ش� �� ����
						ese_Pls[num_final][k] = 'a';
					}
				}
				for (int l = 0; l < num_bit; l++) {//������ ��� Ȯ��
					imsi = final[i][l];
					output << imsi;
					if (final[i][l] == '0') {//0�� ��
						num_zero++;
					}
					else if (final[i][l] == '-') {//-�� ��
						num_blank++;
					}
					else if (final[i][l] == '1') {//1�� ��
						num_one++;
					}
				}
				if (num_bit == num_blank) {//��� ���� blank�ϰ�� �ڵ�����
					tr = 0;
					output << tr;
					cin>> forpause;
					return 0;
				}
				else if (num_bit == num_blank + 1) {//0 Ȥ�� 1�� 1���� ���
					if (num_zero == 1) {//0�ϰ�� inverter�� ���� 2�߰�
						tr += 2;
						num_can++;
					}
				}
				else if (num_bit - num_blank > 1) {//0Ȥ�� 1�� 2���̻��� ���
					tr += (num_bit - num_blank + 1) * 2;//input������ ���� Ʈ�������Ͱ� ���
					if (num_zero - num_one > 0) {//0�� �� ������ (A'*B')=(A+B)'�� ġȯ�� Ʈ�������� ���� ����
						num_can++;
						tr += (num_one + 1) * 2;
					}
					else {
						tr += num_zero * 2;
					}
				}
				num_zero = 0;//0�� �� �ʱ�ȭ
				num_one = 0;//1�� �� �ʱ�ȭ
				num_blank = 0;//-�� �� �ʱ�ȭ
				tr += 2;//�⺻������ ���Ǵ� tr
				num_ese++;
				output << endl;
			}
		}
	}
	for (int j = 0; j <num_care; j++) {//���� X������ 1 �̻��϶� ���� ���� X�� ���Ե� ���� ���� ����
		for (int i = num_final-1; i >=0; i--) {//X�� -�� ���� �Ʒ����� ���
			if (ese_Pls[num_final][j] != 'a'&&ese_Pls[i][j] == 'X') {//������ ������� ���� �� �Ǵ�
				for (int k = 0; k < num_care; k++) {//�ش翭����
					if (ese_Pls[i][k] == 'X' && ese_Pls[num_final][k] != 'a') {
						ese_Pls[num_final][k] = 'a';
					}
				}
				for (int l = 0; l < num_bit; l++) {
					output << final[i][l];//���Ͽ� �Է�
					if (final[i][l] == '0') {//0�Ǽ� ����
						num_zero++;
					}
					else if (final[i][l] == '-') {//-�� �� ����
						num_blank++;
					}
					else if (final[i][l] == '1') {//1�� �� ����
						num_one++;
					}
				}
				if (num_bit == num_blank) {//��� ���� blank�ϰ�� �ڵ����� 
					tr = 0;
					output << "Cost(# of transistors) : " << tr;
					output.close();
					cin >> forpause;
					return 0;
				}
				else if (num_bit == num_blank + 1){//0 Ȥ�� 1�� 1���� ���
					if (num_zero == 1) {//0�ϰ�� inverter�� ���� 2�߰�
						tr += 2;
						num_can++;
					}
				}
				else if (num_bit - num_blank > 1) {//0Ȥ�� 1�� 2���̻��� ���
					tr += (num_bit - num_blank + 1) * 2;//input������ ���� Ʈ�������Ͱ� ���
					if (num_zero - num_one > 0) {//0�� �� ������ (A'*B')=(A+B)'�� ġȯ�� Ʈ�������� ���� ����
						num_can++;
						tr += (num_one + 1) * 2;
					}
					else {
						tr += num_zero * 2;
					}
				}
				num_zero = 0;//0�� �� �ʱ�ȭ
				num_one = 0;//1�� �� �ʱ�ȭ
				num_blank = 0;//-�� �� �ʱ�ȭ
				tr += 2;
				output << endl;
				num_ese++;
				break;
			}
		}
	}
	
	tr += 2;//�⺻ �߰� Ʈ�������� ����
	if (num_ese==1) {//��� ������ 1���� ���
		tr -= 4;
	}
	if (num_can>1) {//(A'*B')=(A+B)'�� ġȯ�� Ʈ�������� ���� ����
		tr -= (num_can - 1) * 2;
	}
	
	output << endl<<"Cost(# of transistors) : " <<tr;//Ʈ���������� ������ ���� �Է�
	num_zero = 0;//0�� �� �ʱ�ȭ
	num_one = 0;//1�� �� �ʱ�ȭ
	num_blank = 0;//-�� �� �ʱ�ȭ
	for (int y = 0; y < row_size; y++) {
		delete[] final[y];
	}
	for (int y = 0; y < num_final+1; y++) { //�����Ҵ����� 2�����迭���� ��ü
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
	output.close();//���� ����
	cin >> forpause;
	return 0;
}