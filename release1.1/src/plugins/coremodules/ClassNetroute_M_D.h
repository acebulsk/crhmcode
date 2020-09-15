//created by Manishankar Mondal

#include "ClassModule.h"

class ClassNetroute_M_D : public ClassModule {
public:

ClassNetroute_M_D(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

long meltrunoffDiv;
long soil_ssrDiv;
long soil_runoffDiv;
long soil_gwDiv;

// declared variables
double *inflow;        // [nhru]
double *cuminflow;     // [nhru]
double *outflow;       // [nhru]
double *outflow_diverted;    // [nhru]
double *cumoutflow_diverted; // [nhru]
double *cumoutflow;    // [nhru]
double *cumscaling_boost;    // [nhru]
double *gwinflow;         // [nhru]
double *gwoutflow_diverted; // [nhru]
double *gwcumoutflow_diverted; // [nhru]
double *HRU_cumbasinflow; // [nhru]

double *ssrinflow;        // [nhru]
double *ssrcuminflow;     // [nhru]
double *ssroutflow;       // [nhru]
double *ssrcumoutflow;    // [nhru]

double *runinflow;        // [nhru]
double *runcuminflow;     // [nhru]
double *runoutflow;       // [nhru]
double *runcumoutflow;    // [nhru]

double *gwoutflow;       // [nhru]
double *gwcuminflow;    // [nhru]
double *gwcumoutflow;    // [nhru]

double *basinflow;     // [BASIN] all HRUs
double *basinflow_s;   // [BASIN] all HRUs
double *cumbasinflow;  // [BASIN] all HRUs
double *basingw;       // [BASIN} all HRUs
double *basingw_s;     // [BASIN} all HRUs
double *cumbasingw;    // [BASIN} all HRUs

double *soil_ssr_Buf;    // buffered
double *soil_runoff_Buf; // buffered
double *soil_gw_Buf;     // buffered

double *cum_to_Sd;         // [nhru]
double *cum_to_soil_rechr; // [nhru]

double *Ktravel;         // [nhru] Muskingum

double *distrib_sum;
double *cum_preferential_flow_to_gw;

ClassMuskingum *hruDelay;
ClassClark *ssrDelay;
ClassClark *runDelay;
ClassClark *gwDelay;

// declared parameters
const double *route_n;         // [nhru]
const double *route_R;         // [nhru]
const double *route_S0;        // [nhru]
const double *route_L;         // [nhru]
const double *route_X_M;       // [nhru]
const long  *route_Cshp;      // [nhru]

const double *Lag;             // [nhru]
const double *ssrKstorage;     // [nhru]
const double *ssrLag;          // [nhru]
const double *runKstorage;     // [nhru]
const double *runLag;          // [nhru]
const double *gwKstorage;      // [nhru]
const double *gwLag;           // [nhru]
const long  *gwwhereto;       // [nhru]

const double *basin_area;      // [BASIN]
const double *hru_area;        // [nhru]
const double *distrib;
const double *distrib_Basin;
const double **distrib_hru;
const double *Sdmax;           // [nhru]
const double *soil_rechr_max;  // [nhru]
const long  *Sd_ByPass;       // [nhru]
const long  *soil_rechr_ByPass; // [nhru]
const long  *order;
const long  *preferential_flow; // [nhru]

const double *scaling_factor;    // temporary modification

// variable inputs
const double *soil_gw;   // [nhru]
const double *soil_ssr;    // [nhru]
const double *soil_runoff; // [nhru]

// variable puts
double *Sd;
double *soil_moist;
double *soil_rechr;
double *redirected_residual;
double *gw;

// local allocated arrays

void decl(void);
void init(void);
void run(void);
void finish(bool good);
virtual double Function1(double *I, long hh);
virtual double Function2(double *X, long hh);

ClassNetroute_M_D* klone(string name) const;
};