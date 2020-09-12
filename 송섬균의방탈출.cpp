#include <bangtal.h>

using namespace bangtal;

int main()
{
	//1. 장면을 생성한다.
	ScenePtr  scene1 = Scene::create("룸1", "images/룸1.png");
	ScenePtr  scene2 = Scene::create("룸2", "images/룸2.png");
	ScenePtr  scene3 = Scene::create("룸3", "images/룸2.png");
	ScenePtr  scene4 = Scene::create("룸4", "images/룸3.png");


	//열쇠를 만든다.
	auto key = Object::create("images/열쇠.png", scene1, 890, 170);
	key->setScale(0.1f);

	key->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		key->pick();
		return true;
		});

	//책을 만든다.
	auto flowerpot_moved = false;
	auto flowerpot = Object::create("images/책.png", scene1, 820, 150);
	flowerpot->setScale(0.13f);
	flowerpot->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (flowerpot_moved == false) {
			if (action == MouseAction::MOUSE_DRAG_LEFT) {
				flowerpot->locate(scene1, 690, 150);
				flowerpot_moved = true;
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				flowerpot->locate(scene1, 930, 150);
				flowerpot_moved = true;
			}
		}
		return true;
		});

	//3. 문을 생성한다.
	auto open1 = false;
	auto door1 = Object::create("images/왼쪽닫힌문.png", scene1, 200, 248);
	door1->setScale(0.5f);

	//4. 문을 클릭하면 이동한다.
	door1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		//5. 문이 열린 상태이면 게임을 종료한다.
		//    문이 닫힌 상태이면 문을 열어준다.
		if (open1 == true) { //문이 열린 상태
			scene2->enter();
		}
		else if (key->isHanded()) { //문이 닫힌 상태
			door1->setImage("images/왼쪽열린문.png");
			open1 = true;
		}
		else {
			showMessage("열쇠가 필요합니다!!");
		}

		return true;
		});

	auto door2 = Object::create("images/왼쪽열린문.png", scene2, 200, 205);
	door2->setScale(0.5f);

	door2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		scene1->enter();
		return true;
		});

	auto open3 = false;
	auto open4 = false;
	auto open5 = false;
	auto open6 = true;

	auto door3 = Object::create("images/오른쪽닫힌문.png", scene1, 920, 330);
	door3->setScale(0.5f);

	door3->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		if (open3 == true && open6 == true) {
			door3->locate(scene1, 822, 328);
			door3->setImage("images/이근.png");
			open3 = false;
			open6 = false;
			open4 = true;
		}
		else if (open4 == true) {
			showMessage("너 인성 문제 있어? 당장 나와!");
			open5 = true;
		}
		else {
			showMessage("전화하고 노크하세요");
		}

		return true;
		});

	door3->setOnKeypadCallback([&](ObjectPtr object)->bool {
		showMessage("따르릉~ 예 노크하세요");
		open3 = true;
		return true;
		});

	auto door4 = Object::create("images/왼쪽닫힌문.png", scene1, 550, 325);
	door4->setScale(0.5f);

	//4. 문을 클릭하면 이동한다.

	auto open7 = false;
	auto open8 = false;
	door4->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		//5. 문이 열린 상태이면 게임을 종료한다.
		//    문이 닫힌 상태이면 문을 열어준다.
		if (open7 == true && open8 == true) { //문이 열린 상태
			scene3->enter();
		}
		else if (key->isHanded() && open8 == true) { //문이 닫힌 상태
			door4->setImage("images/왼쪽열린문.png");
			open7 = true;
		}
		else if (open8 == false) {
			showMessage("공혁준이 막고 있다");
		}
		else
		{
			showMessage("열쇠가 필요합니다");
		}

		return true;
		});

	//공혁준

	auto person = Object::create("images/공혁준.png", scene1, 585, 300);
	person->setScale(0.5f);

	person->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		if (open5 == true) { //비켜야함
			showMessage("악!!!");
			person->locate(scene1, 400, 200);
			open8 = true;
		}
		else {
			showMessage("왜 저만 비켜야 합니까?");
		}

		return true;
		});

	auto phone = Object::create("images/폰.png", scene1, 600, 200);
	phone->setScale(0.4f);
	phone->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		showKeypad("26435", door3);
		return true;
		});

	auto pass = Object::create("images/번호.png", scene2, 600, 370, false);
	pass->setScale(0.7f);

	auto lighted = true;
	auto button = Object::create("images/스위치.png", scene2, 160, 330);
	button->setScale(0.5f);
	button->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (lighted) {
			scene2->setLight(0.2f);
			pass->show();
			lighted = false;
		}
		else {
			scene2->setLight(1.0f);
			pass->hide();
			lighted = true;
		}
		return true;
		});

	auto door8 = Object::create("images/오른쪽열린문.png", scene3, 980, 135);
	door8->setScale(0.5f);

	door8->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		scene1->enter();
		return true;
		});

	auto k1 = false; //총을 받았는가
	auto theend = false;

	auto gun = Object::create("images/총.png", scene3, 10, 10);
	gun->setScale(0.2f);
	gun->hide();

	//에이전트
	auto H = Object::create("images/에이전트.png", scene3, 130, 120);
	H->setScale(0.35f);

	int po[5] = { 0, };

	H->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		if (k1 == false) {
			showMessage("총을 드릴테니 과녁을 모두 제거하세요");
			gun->pick();
			k1 = true;
		}
		else if (po[0] + po[1] + po[2] + po[3] + po[4] == 5) {
			showMessage("휼륭합니다. 문을 열어드리겠습니다.");
			theend = true;
		}
		else {
			showMessage("과녁을 클릭하시면 사격이 진행됩니다");
		}

		return true;
		});


	//과녁
	auto tir = Object::create("images/과녁.png", scene3, 760, 260);
	tir->setScale(0.2f);

	int x2 = 230, y2 = 220, z = 100; //z는 간격

	tir->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (k1 == true) {
			scene4->enter();
		}

		return true;
		});

	auto q1 = Object::create("images/과녁판.png", scene4, 230 + 1 * z, 220 + 2 * z);
	auto q2 = Object::create("images/과녁판.png", scene4, 230 + 3 * z, 220 + 3 * z);
	auto q3 = Object::create("images/과녁판.png", scene4, 230 + 4 * z, 220 + 1 * z);
	auto q4 = Object::create("images/과녁판.png", scene4, 230 + 6 * z, 220 + 0 * z);
	auto q5 = Object::create("images/과녁판.png", scene4, 230 + 8 * z, 220 + 2 * z);
	q1->setScale(0.1f);
	q2->setScale(0.1f);
	q3->setScale(0.1f);
	q4->setScale(0.1f);
	q5->setScale(0.1f);

	//저격 표시
	auto aim = Object::create("images/저격.png", scene4, 230, 220);
	aim->setScale(0.2f);

	//뒤로
	auto bac = Object::create("images/뒤로.png", scene4, 10, 10);
	bac->setScale(0.2f);

	bac->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		scene3->enter();
		return true;
		});


	//방향키
	auto u = Object::create("images/위쪽.png", scene4, 970, 95);
	u->setScale(0.7f);
	auto d = Object::create("images/아래.png", scene4, 970, 10);
	d->setScale(0.7f);
	auto r = Object::create("images/오른쪽.png", scene4, 1055, 10);
	r->setScale(0.7f);
	auto l = Object::create("images/왼쪽.png", scene4, 885, 10);
	l->setScale(0.7f);

	u->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		if (y2 + z <= 220 + 3 * z)
		{
			y2 += z;
			aim->locate(scene4, x2, y2);
		}
		return true;
		});
	d->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		if (y2 - z >= 220)
		{
			y2 -= z;
			aim->locate(scene4, x2, y2);
		}
		return true;
		});
	r->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		if (x2 + z <= 230 + 8 * z)
		{
			x2 += z;
			aim->locate(scene4, x2, y2);
		}
		return true;
		});
	l->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		if (x2 - z >= 230)
		{
			x2 -= z;
			aim->locate(scene4, x2, y2);
		}
		return true;
		});

	//총알쏘기
	auto rr = Object::create("images/총알.png", scene4, 600, 10);
	rr->setScale(0.5f);
	rr->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		if (x2 == 230 + 1 * z && y2 == 220 + 2 * z)
		{
			q1->hide();
			po[0] = 1;
		}
		else if (x2 == 230 + 3 * z && y2 == 220 + 3 * z)
		{
			q2->hide();
			po[1] = 1;
		}
		else if (x2 == 230 + 4 * z && y2 == 220 + 1 * z)
		{
			q3->hide();
			po[2] = 1;
		}
		else if (x2 == 230 + 6 * z && y2 == 220 + 0 * z)
		{
			q4->hide();
			po[3] = 1;
		}
		else if (x2 == 230 + 8 * z && y2 == 220 + 2 * z)
		{
			q5->hide();
			po[4] = 1;
		}

		return true;
		});

	auto fds = false;

	auto door9 = Object::create("images/오른쪽닫힌문.png", scene3, 550, 250);
	door9->setScale(0.5f);

	door9->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		if (theend == true)
		{
			door9->setImage("images/오른쪽열린문.png");
			fds = true;
			theend =false;
		}
		else if (fds == true)
			endGame();

		return true;
		});

	//2. 게임을 시작한다.
	startGame(scene1);


	return 0;
}