#include <iostream>

using namespace std;
// 友元类

class Tv {
	private:
		enum {off, on};
		enum {minchn, maxchn=50};
		bool m_on_off;
		int m_volume;
		int m_channel;
	public:
		Tv(bool on_off, int volume, int channel);
		void show();
		// 友元类
		friend class TvController;
};
Tv::Tv(bool on_off, int volume, int channel):\
		m_on_off(on_off), m_volume(volume), m_channel(channel){}

void Tv::show() 
{
	cout << "on_off" << m_on_off << endl;
	cout << "volume" << m_volume << endl;
	cout << "channel" << m_channel << endl;
}

class TvController {
	public:
		void setStatus(Tv *t);
		void volumn_up(Tv *t);
		void volumn_down(Tv *t);
		void channel_up(Tv *t);
		void channel_down(Tv *t);
};
void TvController::setStatus(Tv *t)
{
	t->m_on_off = (t->m_on_off == t->on ? t->off : t->on);
}
void TvController::volumn_up(Tv *t)
{
	if (t->m_volume < 100) {
		t->m_volume ++;
	}
}
void TvController::volumn_down(Tv *t)
{
	if (t->m_volume > 0)
		t->m_volume --;
}
void TvController::channel_up(Tv *t)
{
	t->m_channel = (t->m_channel+1) % t->maxchn;
}
void TvController::channel_down(Tv *t)
{
	if (t->m_channel > 0)
		t->m_channel--;
	else
		t->m_channel= 49;
}

int main(void)
{
	Tv tv(false, 20, 3);
	TvController ctl;

	ctl.setStatus(&tv);
	ctl.volumn_up(&tv);
	ctl.channel_up(&tv);
	tv.show();

	return 0;
}

