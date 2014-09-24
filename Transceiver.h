#ifndef TRANSCEIVER_H_
#define TRANSCEIVER_H_

/**
 * \brief    Parent for UDP and TCP ...
 * \details  Parent for UDP and TCP ...  not allways usefull, but sometimes it might be.
 * \author   Ingo Breuer (ingo.breuer@hhu.de)
 */
class Transceiver {
protected:
	Transceiver();
public:
	virtual ~Transceiver();
	virtual int send(const char*, const unsigned, const int = 0) = 0;
	virtual int recv(char *, const unsigned, const int = 0) = 0;
};

#endif
