/*
 * GPSupdater.h
 *
 *  Created on: May 19, 2015
 *      Author: sailbot
 */

#ifndef GPS_GPSUPDATER_H_
#define GPS_GPSUPDATER_H_

class GPSupdater {

	public:
		GPSupdater(GPSReader *reader);
		~GPSupdater(){};
		void run();
		void close();

	private:
		GPSReader m_gpsReader;
		std::mutex m_mutex;
		bool m_running;

		bool isRunning();
};

#endif /* GPS_GPSUPDATER_H_ */
