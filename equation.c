//방정식 가지고 노는 코드
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>
#define MAX_TERMS 80

typedef struct {
	int expo; //지수
	double coef; //계수
} Term;

typedef struct {
	int nTerm; //계수가 0이 아닌 항의 개수
	Term term[MAX_TERMS]; //항의 배열
} SparsePoly;

double evaluate(SparsePoly, double);
SparsePoly add(SparsePoly, SparsePoly);
SparsePoly sub(SparsePoly, SparsePoly);
void printSpoly(SparsePoly, char*);

int main(void)
{
	SparsePoly a = { 2, {{100, 10.f},{0, 6.0f}} };
	SparsePoly b = { 2, {{50, 1.1f},{3, 2.0f}} };
	SparsePoly c = add(a, b);
	SparsePoly d = sub(a, b);
	printSpoly(a, "a = ");
	printSpoly(b, "b = ");
	printSpoly(c, "c = ");
	printSpoly(d, "d = ");
	printf("a(1) = %lf\n", evaluate(a, 1.0f));
	printf("b(2) = %lf\n", evaluate(b, 2.0f));

	return 0;
}

double evaluate(SparsePoly a, double x) {
	double result = 0;
	int i;
	for (i = 0; i < a.nTerm; i++) {
		result = result + a.term[i].coef * pow(x, a.term[i].expo);
	}
	return result;
}

SparsePoly add(SparsePoly A, SparsePoly B) {
	SparsePoly c;
	int i, j;
	c.nTerm = 0;
	for (i = 0, j = 0; i < A.nTerm || j < B.nTerm;) {
		if (i == A.nTerm || A.term[i].expo < B.term[j].expo) {
			c.term[c.nTerm] = B.term[j];
			c.nTerm++;
			j++;
		}
		else if (j == B.nTerm || A.term[i].expo > B.term[j].expo) {
			c.term[c.nTerm] = A.term[i];
			c.nTerm++;
			i++;
		}
		else {
			c.term[c.nTerm] = A.term[i];
			i++;
			c.term[c.nTerm].coef += B.term[j].coef;
			c.nTerm++;
			j++;
		}
	}
	return c;
}

SparsePoly sub(SparsePoly A, SparsePoly B) {
	SparsePoly c;
	int i, j;
	c.nTerm = 0;
	for (i = 0, j = 0; i < A.nTerm || j < B.nTerm;) {
		if (i == A.nTerm || A.term[i].expo < B.term[j].expo) {
			c.term[c.nTerm].expo = B.term[j].expo;
			c.term[c.nTerm].coef = -B.term[j].coef;
			c.nTerm++;
			j++;
		}
		else if (j == B.nTerm || A.term[i].expo > B.term[j].expo) {
			c.term[c.nTerm] = A.term[i];
			c.nTerm++;
			i++;
		}
		else {
			c.term[c.nTerm] = A.term[i];
			i++;
			c.term[c.nTerm].coef -= B.term[j].coef;
			c.nTerm++;
			j++;
		}
	}
	return c;
}

void printSpoly(SparsePoly a, char* str) {
	int i;
	printf("%s", str);
	for (i = 0; i < a.nTerm; i++) {
		printf("%5.1lf", a.term[i].coef);
		if (a.term[i].expo > 0) {
			printf(" x^%d ", a.term[i].expo);
			if (i != a.nTerm - 1) {
				printf("+ ");
			}
		}
	}
	printf("\n");
}