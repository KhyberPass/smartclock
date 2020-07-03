
typedef enum {
	Config_Display_Sleep,
	Config_End
} sclockConfig_t;


int sclockConfigGet(int id) {
  switch (id)
  {
    case Config_Display_Sleep:
      return 1;
      break;
    
    default:
      break;
  }
}
  
