#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>


struct Wifi_Config_Struct {
	int station_mode_active;
	char *station_ssid;
	char *station_password;
	char *station_protocol;
	int ap_mode_active;
	char *ap_ssid;
	char *ap_password;
};

void config_wifi(struct Wifi_Config_Struct wifi_settings)
{

	size_t buffer = 100;
	int mode_avtive;
	int Mode;
	char line[buffer];
	char file_path[]="/wifi.d/wifi_ap+sta"; // source file location
	FILE *fp_template;
	FILE *fp_final;

	if ((wifi_settings.ap_mode_active==0) && (wifi_settings.station_mode_active==0)) {
		Mode=2;
		printf("ap + sta mode\n");
	}
	else if(wifi_settings.ap_mode_active==0) {
		Mode=1;
		printf("only wifi ap mode\n");
	}
	else if(wifi_settings.station_mode_active==0) {
		Mode=0;
		printf("only wifi station mode\n");
	}

	if ((fp_template = fopen(file_path, "r")) == NULL)
	{
		//printf ("File could not be opened\n");
		printf("Wireless file could not be opened");
		return;
	}

// target file location -- filw which you want to change
	if ((fp_final = fopen("/file/you/want/to/change", "w")) == NULL)
	{
		//printf ("File could not be opened\n");
		printf("Wireless file could not be opened");
		fclose(fp_template);
		return;
	}

	while (fgets(line, buffer, fp_template) != NULL)
	{
		if (strstr(line, "**ap_activation**") != NULL)
		{
			if (Mode != 0) {
				// ap mode enabling
				fprintf(fp_final, "	option disabled \'0\'\n");
			}
			else {
				// ap mode disabling
				fprintf(fp_final, "	option disabled \'1\'\n");
			}
			continue;
		}
		else if (strstr(line, "**ap_ssid**") != NULL) {
			if (Mode != 0) {
				// ssid for ap
				fprintf(fp_final, "	option ssid \'%s\'\n", wifi_settings.ap_ssid););
			}
			continue;
		}
		else if (strstr(line, "**ap_passw**") != NULL) {
			if (Mode !=0) {
				// password for ap
				fprintf(fp_final, "	option key \'%s\'\n", wifi_settings.ap_password);
			}
			continue;
		}
		if (strstr(line, "**sta_activation**") != NULL)
		{
			if (Mode != 1) {
				// station mode enabling
				fprintf(fp_final, "	option disabled \'0\'\n");
			}
			else {
				// station mode disabling
				fprintf(fp_final, "	option disabled \'1\'\n");
			}
			continue;
		}
		else if (strstr(line, "**sta_ssid**") != NULL) {
			if (Mode != 1) {
				// ssid for station mode
				fprintf(fp_final, "	option ssid \'%s\'\n", wifi_settings.station_ssid);
			}
			continue;
		}
		else if (strstr(line, "**sta_passw") != NULL) {
			if (Mode != 1) {
				// password for station mode
				fprintf(fp_final, "	option key \'%s\'\n", wifi_settings.station_password);
			}
			continue;
		}
		else if (strstr(line, "**sta_protocol**") != NULL){
			// encryption method for station mode
			fprintf(fp_final, "	option encryption \'%s\'\n", wifi_settings.station_protocol);
			continue;
		}
		else
		{
			fputs(line, fp_final);
		}
	}

	fclose (fp_final);
	fclose (fp_template);
	system("/etc/init.d/network reload");
	// sleep(10);
	printf("check your.... files its been edited!!!!");
	return;

}

void main() {

	// To activate the individual mode,
	// 0 should be assigned to respected mode_active member of structure
	struct Wifi_Config_Struct wifi;
	wifi.station_mode_active=0;
	wifi.station_ssid="guest-wifi";
	wifi.station_password="trythis";
	wifi.station_protocol="psk";
	wifi.ap_mode_active=1;


	config_wifi(wifi);
}
