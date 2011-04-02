#include "Julian.h"
#include "Tle.h"
#include "SGDP4.h"
#include "Globals.h"
#include "Observer.h"
#include "Coord.h"

#include <list>
#include <string>
#include <iomanip>

void RunTest();

int main() {
#if 0
    std::list<Tle> tles;

    tles.push_back(Tle("ALSAT 1                 ",
            "1 27559U 02054A   11089.12872679  .00000243  00000-0  48843-4 0  4131",
            "2 27559  97.8507 312.4200 0024709  79.8694 280.5316 14.69495914445317"));
    tles.push_back(Tle("NIGERIASAT 1            ",
            "1 27941U 03042C   11089.42378502  .00000216  00000-0  50713-4 0  4761",
            "2 27941  97.8561 306.5880 0010368 237.5473 122.4725 14.63159222400765"));
    tles.push_back(Tle("UK-DMC                  ",
            "1 27942U 03042D   11089.21347025  .00000290  00000-0  48646-4 0  4961",
            "2 27942  97.8664 309.9311 0065103 241.0875 118.3788 14.75706603400968"));
    tles.push_back(Tle("BILSAT 1                ",
            "1 27943U 03042E   11089.08572765  .00000047  00000-0  17816-4 0  3300",
            "2 27943  97.8538 305.4240 0010467 236.5131 123.5076 14.63002695400693"));
    tles.push_back(Tle("BEIJING 1               ",
            "1 28890U 05043A   11089.11363757  .00000109  00000-0  31969-4 0  2110",
            "2 28890  97.9674 327.9265 0016808 104.1515 256.1558 14.60145019288893"));
    tles.push_back(Tle("HJ-1A                   ",
            "1 33320U 08041A   11089.11645018  .00000558  00000-0  89157-4 0  8293",
            "2 33320  97.9120 163.4564 0025524 145.5493 214.7394 14.75434524137863"));
    tles.push_back(Tle("HJ-1B                   ",
            "1 33321U 08041B   11089.08261697  .00000036  00000-0  12683-4 0  8669",
            "2 33321  97.9143 163.5499 0043578 158.5982 201.7100 14.75426284137846"));
    tles.push_back(Tle("YAOGAN 4                ",
            "1 33446U 08061A   11089.08015953 -.00000298  00000-0 -37502-4 0  5825",
            "2 33446  97.8391 162.8578 0018973  95.0341 265.3034 14.74341232125165"));
    tles.push_back(Tle("YAOGAN 5                ",
            "1 33456U 08064A   11089.23155758  .00004620  00000-0  16914-3 0  5761",
            "2 33456  97.3037 163.0372 0010288 244.1979 149.0647 15.28479448127350"));
    tles.push_back(Tle("DEIMOS-1                ",
            "1 35681U 09041A   11089.07598815  .00000232  00000-0  47449-4 0  8526",
            "2 35681  98.0731 349.0935 0001647  77.8673 282.2722 14.69439966 89360"));
    tles.push_back(Tle("UK-DMC 2                ",
            "1 35683U 09041C   11089.11558659  .00000272  00000-0  54146-4 0  8712",
            "2 35683  98.0762 348.1067 0001434  99.8921 260.2456 14.69414094 89293"));

    //tles.push_back(Tle("SGP4 Test",
    //        "1 88888U          80275.98708465  .00073094  13844-3  66816-4 0     8",
    //        "2 88888  72.8435 115.9689 0086731  52.6988 110.5714 16.05824518   105"));

    //tles.push_back(Tle("SDP4 Test",
    //        "1 11801U          80230.29629788  .01431103  00000-0  14311-1      13",
    //        "2 11801  46.7916 230.4354 7318036  47.4722  10.4117  2.28537848    13"));

    Observer obs(51.360242, 0.101473, 0.07);

    std::list<Tle>::iterator itr;

    while (true) {
        Julian date_now;

        for (itr = tles.begin(); itr != tles.end(); itr++) {
            SGDP4 model;
            double tsince = date_now.SpanMin((*itr).GetEpoch());
            model.SetTle(*itr);
            Eci eci;
            model.FindPosition(eci, tsince);
            CoordTopographic topo = obs.GetLookAngle(eci);

            std::cout.width(17);
            std::cout << itr->GetName() << " ";
            std::cout << std::setprecision(8) << std::fixed;
            std::cout.width(17);
            std::cout << tsince << " ";
            std::cout.width(17);
            std::cout << Globals::Rad2Deg(topo.GetAzimuth()) << " ";
            std::cout.width(17);
            std::cout << Globals::Rad2Deg(topo.GetElevation()) << std::endl;
        }
    }
#endif

    RunTest();
    return 0;
}

void RunTle(Tle tle, double start, double end, double inc) {
    double current = start;
    SGDP4 model;
    model.SetTle(tle);
    bool running = true;
    bool first_run = true;
    std::cout << "  " << tle.GetName() << "  xx" << std::endl;
    while (running) {
        try {
            double val;
            Eci eci;
            if (first_run && current != 0.0) {
                /*
                 * make sure first run is always as zero
                 */
                val = 0.0;
            } else {
                /*
                 * otherwise run as normal
                 */
                val = current;
            }
            model.FindPosition(eci, val);

            Vector position = eci.GetPosition();

            std::cout << std::setprecision(8) << std::fixed;
            std::cout.width(17);
            std::cout << val << " ";
            std::cout.width(16);
            std::cout << position.GetX() << " ";
            std::cout.width(16);
            std::cout << position.GetY() << " ";
            std::cout.width(16);
            std::cout << position.GetZ() << std::endl;

        } catch (std::exception* ex) {
            std::cout << ex->what() << std::endl;
            running = false;
        }
        if ((first_run && current == 0.0) || !first_run) {
            if (current == end)
                running = false;
            else if (current + inc > end)
                current = end;
            else
                current += inc;
        }
        first_run = false;

    }
}

void RunTest() {

#if 0

    /*
      #   ------------------ Verification test cases ----------------------
      #                       # TEME example
      1 00005U 58002B   00179.78495062  .00000023  00000-0  28098-4 0  4753
      2 00005  34.2682 348.7242 1859667 331.7664  19.3264 10.82419157413667     0.00      4320.0        360.00
     */
    RunTle(Tle("00005",
            "1 00005U 58002B   00179.78495062  .00000023  00000-0  28098-4 0  4753",
            "2 00005  34.2682 348.7242 1859667 331.7664  19.3264 10.82419157413667"), 0.0, 4320.0, 360.0);


    /*
    #                       ## fig show lyddane fix error with gsfc ver
    1 04632U 70093B   04031.91070959 -.00000084  00000-0  10000-3 0  9955
    2 04632  11.4628 273.1101 1450506 207.6000 143.9350  1.20231981 44145  -5184.0     -4896.0        120.00
     */
    RunTle(Tle("04632",
            "1 04632U 70093B   04031.91070959 -.00000084  00000-0  10000-3 0  9955",
            "2 04632  11.4628 273.1101 1450506 207.6000 143.9350  1.20231981 44145"), -5184.0, -4896.0, 120.0);


    /*
    #   DELTA 1 DEB         # near earth normal drag equation
    #                       # perigee = 377.26km, so moderate drag case
    1 06251U 62025E   06176.82412014  .00008885  00000-0  12808-3 0  3985
    2 06251  58.0579  54.0425 0030035 139.1568 221.1854 15.56387291  6774      0.0      2880.0        120.00
     */
    RunTle(Tle("06251",
            "1 06251U 62025E   06176.82412014  .00008885  00000-0  12808-3 0  3985",
            "2 06251  58.0579  54.0425 0030035 139.1568 221.1854 15.56387291  6774"), 0.0, 2880.0, 120.0);


    /*
    #   MOLNIYA 2-14              # 12h resonant ecc in 0.65 to 0.7 range
    1 08195U 75081A   06176.33215444  .00000099  00000-0  11873-3 0   813
    2 08195  64.1586 279.0717 6877146 264.7651  20.2257  2.00491383225656      0.0      2880.0        120.00
     */
    RunTle(Tle("08195",
            "1 08195U 75081A   06176.33215444  .00000099  00000-0  11873-3 0   813",
            "2 08195  64.1586 279.0717 6877146 264.7651  20.2257  2.00491383225656"), 0.0, 2880.0, 120.0);


    /*
    #   MOLNIYA 1-36              ## fig 12h resonant ecc in 0.7 to 0.715 range
    1 09880U 77021A   06176.56157475  .00000421  00000-0  10000-3 0  9814
    2 09880  64.5968 349.3786 7069051 270.0229  16.3320  2.00813614112380      0.0      2880.0        120.00
     */
    RunTle(Tle("09880",
            "1 09880U 77021A   06176.56157475  .00000421  00000-0  10000-3 0  9814",
            "2 08195  64.5968 349.3786 7069051 270.0229  16.3320  2.00813614112380"), 0.0, 2880.0, 120.0);


    /*
    #   SMS 1 AKM           # show the integrator problem with gsfc ver
    1 09998U 74033F   05148.79417928 -.00000112  00000-0  00000+0 0  4480
    2 09998   9.4958 313.1750 0270971 327.5225  30.8097  1.16186785 45878  -1440.0      -720.00         60.0
     */
    RunTle(Tle("09998",
            "1 09998U 74033F   05148.79417928 -.00000112  00000-0  00000+0 0  4480",
            "2 09998   9.4958 313.1750 0270971 327.5225  30.8097  1.16186785 45878"), -1440.0, -720.0, 60.0);


    /*
    #                       # Original STR#3 SDP4 test
    1 11801U          80230.29629788  .01431103  00000-0  14311-1      13
    2 11801  46.7916 230.4354 7318036  47.4722  10.4117  2.28537848    13      0.0      1440.0        360.00
     */
    RunTle(Tle("11801",
            "1 11801U          80230.29629788  .01431103  00000-0  14311-1      13",
            "2 11801  46.7916 230.4354 7318036  47.4722  10.4117  2.28537848    13"), 0.0, 1440.0, 360.0);


    /*
   #   EUTELSAT 1-F1 (ECS1)## fig lyddane choice in GSFC at 2080 min
   1 14128U 83058A   06176.02844893 -.00000158  00000-0  10000-3 0  9627
   2 14128  11.4384  35.2134 0011562  26.4582 333.5652  0.98870114 46093      0.0      2880.0        120.00
     */
    RunTle(Tle("14128",
            "1 14128U 83058A   06176.02844893 -.00000158  00000-0  10000-3 0  9627",
            "2 14128  11.4384  35.2134 0011562  26.4582 333.5652  0.98870114 46093"), 0.0, 2880.0, 120.0);


    /*
    #   SL-6 R/B(2)         # Deep space, perigee = 82.48 (<98) for
    #                       # s4 > 20 mod
    1 16925U 86065D   06151.67415771  .02550794 -30915-6  18784-3 0  4486
    2 16925  62.0906 295.0239 5596327 245.1593  47.9690  4.88511875148616      0.0      1440.0        120.00
     */
    RunTle(Tle("16925",
            "1 16925U 86065D   06151.67415771  .02550794 -30915-6  18784-3 0  4486",
            "2 16925  62.0906 295.0239 5596327 245.1593  47.9690  4.88511875148616"), 0.0, 1440.0, 120.0);


    /*
    #   SL-12 R/B           # Shows Lyddane choice at 1860 and 4700 min
    1 20413U 83020D   05363.79166667  .00000000  00000-0  00000+0 0  7041
    2 20413  12.3514 187.4253 7864447 196.3027 356.5478  0.24690082  7978   1440.0      4320.0        120.00
     */
    RunTle(Tle("20413",
            "1 20413U 83020D   05363.79166667  .00000000  00000-0  00000+0 0  7041",
            "2 20413  12.3514 187.4253 7864447 196.3027 356.5478  0.24690082  7978"), 1440.0, 4320.0, 120.0);


    /*
    #   MOLNIYA 1-83                # 12h resonant, ecc > 0.715 (negative BSTAR)
    1 21897U 92011A   06176.02341244 -.00001273  00000-0 -13525-3 0  3044
    2 21897  62.1749 198.0096 7421690 253.0462  20.1561  2.01269994104880      0.0      2880.0        120.00
     */
    RunTle(Tle("21897",
            "1 21897U 92011A   06176.02341244 -.00001273  00000-0 -13525-3 0  3044",
            "2 21897  62.1749 198.0096 7421690 253.0462  20.1561  2.01269994104880"), 0.0, 2880.0, 120.0);


    /*
    #   SL-6 R/B(2)         # last tle given, decayed 2006-04-04, day 94
    1 22312U 93002D   06094.46235912  .99999999  81888-5  49949-3 0  3953
    2 22312  62.1486  77.4698 0308723 267.9229  88.7392 15.95744531 98783  54.2028672   1440.0         20.00
     */
    RunTle(Tle("22312",
            "1 22312U 93002D   06094.46235912  .99999999  81888-5  49949-3 0  3953",
            "2 22312  62.1486  77.4698 0308723 267.9229  88.7392 15.95744531 98783"), 54.2028672, 1440.0, 20.0);


    /*
    #   SL-6 R/B(2)         # 12h resonant ecc in the > 0.715 range
    1 22674U 93035D   06176.55909107  .00002121  00000-0  29868-3 0  6569
    2 22674  63.5035 354.4452 7541712 253.3264  18.7754  1.96679808 93877      0.0      2880.0        120.00
     */
    RunTle(Tle("22674",
            "1 22674U 93035D   06176.55909107  .00002121  00000-0  29868-3 0  6569",
            "2 22674  63.5035 354.4452 7541712 253.3264  18.7754  1.96679808 93877"), 0.0, 2880.0, 120.0);


    /*
    #   ARIANE 44L+ R/B     # Lyddane bug at <= 70 min for atan2(),
    #                       # no quadrant fix
    1 23177U 94040C   06175.45752052  .00000386  00000-0  76590-3 0    95
    2 23177   7.0496 179.8238 7258491 296.0482   8.3061  2.25906668 97438      0.0      1440.0        120.00
     */
    RunTle(Tle("23177",
            "1 23177U 94040C   06175.45752052  .00000386  00000-0  76590-3 0    95",
            "2 23177   7.0496 179.8238 7258491 296.0482   8.3061  2.25906668 97438"), 0.0, 1440.0, 120.0);


    /*
    #   WIND                        # STR#3 Kepler failes past about 200 min
    1 23333U 94071A   94305.49999999 -.00172956  26967-3  10000-3 0    15
    2 23333  28.7490   2.3720 9728298  30.4360   1.3500  0.07309491    70      0.0      1600.0        120.00
     */
    RunTle(Tle("23333",
            "1 23333U 94071A   94305.49999999 -.00172956  26967-3  10000-3 0    15",
            "2 23333  28.7490   2.3720 9728298  30.4360   1.3500  0.07309491    70"), 0.0, 1600.0, 120.0);


    /*
    #   ARIANE 42P+3 R/B    ## fig Lyddane bug at > 280.5 min for AcTan()
    1 23599U 95029B   06171.76535463  .00085586  12891-6  12956-2 0  2905
    2 23599   6.9327   0.2849 5782022 274.4436  25.2425  4.47796565123555      0.0       720.0         20.00
     */
    RunTle(Tle("23599",
            "1 23599U 95029B   06171.76535463  .00085586  12891-6  12956-2 0  2905",
            "2 23599   6.9327   0.2849 5782022 274.4436  25.2425  4.47796565123555"), 0.0, 720.0, 20.0);


    /*
    #   ITALSAT 2           # 24h resonant GEO, inclination > 3 deg
    1 24208U 96044A   06177.04061740 -.00000094  00000-0  10000-3 0  1600
    2 24208   3.8536  80.0121 0026640 311.0977  48.3000  1.00778054 36119      0.0      1440.0        120.00
     */
    RunTle(Tle("24208",
            "1 24208U 96044A   06177.04061740 -.00000094  00000-0  10000-3 0  1600",
            "2 24208   3.8536  80.0121 0026640 311.0977  48.3000  1.00778054 36119"), 0.0, 1440.0, 120.0);


    /*
    #   AMC-4               ## fig low incl, show incl shift with
    #                       ## gsfc version from 240 to 1440 min
    1 25954U 99060A   04039.68057285 -.00000108  00000-0  00000-0 0  6847
    2 25954   0.0004 243.8136 0001765  15.5294  22.7134  1.00271289 15615  -1440.0      1440.0        120.00
     */
    RunTle(Tle("25954",
            "1 25954U 99060A   04039.68057285 -.00000108  00000-0  00000-0 0  6847",
            "2 25954   0.0004 243.8136 0001765  15.5294  22.7134  1.00271289 15615"), -1440.0, 1400.0, 120.0);


    /*
    #   INTELSAT 902                # negative incl at 9313 min then
    #                       # 270 deg Lyddane bug at 37606 min
    1 26900U 01039A   06106.74503247  .00000045  00000-0  10000-3 0  8290
    2 26900   0.0164 266.5378 0003319  86.1794 182.2590  1.00273847 16981   9300.00     9400.00        60.00
     */
    RunTle(Tle("26900",
            "1 26900U 01039A   06106.74503247  .00000045  00000-0  10000-3 0  8290",
            "2 26900   0.0164 266.5378 0003319  86.1794 182.2590  1.00273847 16981"), 9300.0, 9400.0, 60.0);


    /*
    #   COSMOS 1024 DEB     # 12h resonant ecc in 0.5 to 0.65 range
    1 26975U 78066F   06174.85818871  .00000620  00000-0  10000-3 0  6809
    2 26975  68.4714 236.1303 5602877 123.7484 302.5767  2.05657553 67521      0.0      2880.0        120.00
     */
    RunTle(Tle("26975",
            "1 26975U 78066F   06174.85818871  .00000620  00000-0  10000-3 0  6809",
            "2 26975  68.4714 236.1303 5602877 123.7484 302.5767  2.05657553 67521"), 0.0, 2880.0, 120.0);


    /*
    #   CBERS 2                     # Near Earth, ecc = 8.84E-5 (< 1.0e-4)
    #                       # drop certain normal drag terms
    1 28057U 03049A   06177.78615833  .00000060  00000-0  35940-4 0  1836
    2 28057  98.4283 247.6961 0000884  88.1964 271.9322 14.35478080140550      0.0      2880.0        120.00
     */
    RunTle(Tle("28057",
            "1 28057U 03049A   06177.78615833  .00000060  00000-0  35940-4 0  1836",
            "2 28057  98.4283 247.6961 0000884  88.1964 271.9322 14.35478080140550"), 0.0, 2880.0, 120.0);


    /*
    #   NAVSTAR 53 (USA 175)# 12h non-resonant GPS (ecc < 0.5 ecc)
    1 28129U 03058A   06175.57071136 -.00000104  00000-0  10000-3 0   459
    2 28129  54.7298 324.8098 0048506 266.2640  93.1663  2.00562768 18443      0.0      1440.0        120.00
     */
    RunTle(Tle("28129",
            "1 28129U 03058A   06175.57071136 -.00000104  00000-0  10000-3 0   459",
            "2 28129  54.7298 324.8098 0048506 266.2640  93.1663  2.00562768 18443"), 0.0, 1440.0, 120.0);


    /*
    #   COSMOS 2405         # Near Earth, perigee = 127.20 (< 156) s4 mod
    1 28350U 04020A   06167.21788666  .16154492  76267-5  18678-3 0  8894
    2 28350  64.9977 345.6130 0024870 260.7578  99.9590 16.47856722116490      0.0      2880.0        120.00
     */
    RunTle(Tle("28350",
            "1 28350U 04020A   06167.21788666  .16154492  76267-5  18678-3 0  8894",
            "2 28350  64.9977 345.6130 0024870 260.7578  99.9590 16.47856722116490"), 0.0, 2880.0, 120.0);
    //#endif

    /*
    #   H-2 R/B                   # Deep space, perigee = 135.75 (<156) s4 mod
    1 28623U 05006B   06177.81079184  .00637644  69054-6  96390-3 0  6000
    2 28623  28.5200 114.9834 6249053 170.2550 212.8965  3.79477162 12753      0.0      1440.0        120.00
     */
    RunTle(Tle("28623",
            "1 28623U 05006B   06177.81079184  .00637644  69054-6  96390-3 0  6000",
            "2 28623  28.5200 114.9834 6249053 170.2550 212.8965  3.79477162 12753"), 0.0, 1440.0, 120.0);

    //    return;
    /*
    #   XM-3                      # 24h resonant geo, incl < 3 deg goes
    #                       # negative around 1130 min
    1 28626U 05008A   06176.46683397 -.00000205  00000-0  10000-3 0  2190
    2 28626   0.0019 286.9433 0000335  13.7918  55.6504  1.00270176  4891      0.0      1440.0        120.00
     */
    RunTle(Tle("28626",
            "1 28626U 05008A   06176.46683397 -.00000205  00000-0  10000-3 0  2190",
            "2 28626   0.0019 286.9433 0000335  13.7918  55.6504  1.00270176  4891"), 0.0, 1440.0, 120.0);


    /*
    #   MINOTAUR R/B        # Sub-orbital case - Decayed 2005-11-29
    #                       #(perigee = -51km), lost in 50 minutes
    1 28872U 05037B   05333.02012661  .25992681  00000-0  24476-3 0  1534
    2 28872  96.4736 157.9986 0303955 244.0492 110.6523 16.46015938 10708      0.0        60.0          5.00
     */
    RunTle(Tle("28872",
            "1 28872U 05037B   05333.02012661  .25992681  00000-0  24476-3 0  1534",
            "2 28872  96.4736 157.9986 0303955 244.0492 110.6523 16.46015938 10708"), 0.0, 50.0, 5.0);

#endif
    /*
    #   SL-14 DEB           # Last stage of decay - lost in under 420 min
    1 29141U 85108AA  06170.26783845  .99999999  00000-0  13519-0 0   718
    2 29141  82.4288 273.4882 0015848 277.2124  83.9133 15.93343074  6828      0.0       440.0         20.00
     */
    RunTle(Tle("29141",
            "1 29141U 85108AA  06170.26783845  .99999999  00000-0  13519-0 0   718",
            "2 29141  82.4288 273.4882 0015848 277.2124  83.9133 15.93343074  6828"), 0.0, 420.0, 20.0);

return;
    /*
    #   SL-12 DEB           # Near Earth, perigee = 212.24 < 220
    #                       # simplified drag eq
    1 29238U 06022G   06177.28732010  .00766286  10823-4  13334-2 0   101
    2 29238  51.5595 213.7903 0202579  95.2503 267.9010 15.73823839  1061      0.0      1440.0        120.00
     */
    RunTle(Tle("29238",
            "1 29238U 06022G   06177.28732010  .00766286  10823-4  13334-2 0   101",
            "2 29238  51.5595 213.7903 0202579  95.2503 267.9010 15.73823839  1061"), 0.0, 1440.0, 120.0);


    /*
    #                       # Original STR#3 SGP4 test
    1 88888U          80275.98708465  .00073094  13844-3  66816-4 0    87
    2 88888  72.8435 115.9689 0086731  52.6988 110.5714 16.05824518  1058      0.0      1440.0        120.00
     */
    RunTle(Tle("88888",
            "1 88888U          80275.98708465  .00073094  13844-3  66816-4 0    87",
            "2 88888  72.8435 115.9689 0086731  52.6988 110.5714 16.05824518  1058"), 0.0, 1440.0, 120.0);


    /*
    #
    #                       # check error code 4
    1 33333U 05037B   05333.02012661  .25992681  00000-0  24476-3 0  1534
    2 33333  96.4736 157.9986 9950000 244.0492 110.6523  4.00004038 10708      0.0       150.0          5.00
     */
    //RunTle(Tle("33333",
    //        "1 33333U 05037B   05333.02012661  .25992681  00000-0  24476-3 0  1534",
    //        "2 33333  96.4736 157.9986 9950000 244.0492 110.6523  4.00004038 10708"), 0.0, 150.0, 5.0);


    /*
    #                       # try and check error code 2 but this
    1 33334U 78066F   06174.85818871  .00000620  00000-0  10000-3 0  6809
    2 33334  68.4714 236.1303 5602877 123.7484 302.5767  0.00001000 67521      0.0      1440.0         1.00
     */
    //RunTle(Tle("33334",
    //        "1 33334U 78066F   06174.85818871  .00000620  00000-0  10000-3 0  6809",
    //        "2 33334  68.4714 236.1303 5602877 123.7484 302.5767  0.00001000 67521"), 0.0, 1440.0, 1.0);


    /*
    #                       # try to check error code 3 looks like ep never goes below zero, tied close to ecc
    1 33335U 05008A   06176.46683397 -.00000205  00000-0  10000-3 0  2190
    2 33335   0.0019 286.9433 0000004  13.7918  55.6504  1.00270176  4891      0.0      1440.0         20.00
     */
    //RunTle(Tle("33335",
    //        "1 33335U 05008A   06176.46683397 -.00000205  00000-0  10000-3 0  2190",
    //        "2 33335   0.0019 286.9433 0000004  13.7918  55.6504  1.00270176  4891"), 0.0, 1440.0, 20.0);


    /*
     #   SL-12 R/B           # Shows Lyddane choice at 1860 and 4700 min
     1 20413U 83020D   05363.79166667  .00000000  00000-0  00000+0 0  7041
     2 33335   0.0019 286.9433 0000004  13.7918  55.6504  1.00270176  4891      0.0      1440.0         20.00
     */
    //RunTle(Tle("20413",
    //        "1 20413U 83020D   05363.79166667  .00000000  00000-0  00000+0 0  7041",
    //        "2 20413  12.3514 187.4253 7864447 196.3027 356.5478  0.24690082  7978"), 1844000.0, 1845100.0, 5.0);


}
