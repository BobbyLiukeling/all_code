class Coordinate
{
public:
	Coordinate(int x, int y);
	~Coordinate();
	void setX(int x);
	void setY(int y);
	int getX()const;
	int getY()const;
private:
	int m_iX;
	int m_iY;
};

