#ifndef TRANSCEIVER_H_
#define TRANSCEIVER_H_

class Transceiver {
protected:
	Transceiver();
public:
	virtual ~Transceiver();
	virtual int send(const char*, const unsigned, const int = 0) = 0;
	virtual int recv(char *, const unsigned, const int = 0) = 0;
};

#endif
