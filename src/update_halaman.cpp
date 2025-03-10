#include "update_halaman.h"

data_parse dps;

void update_monitor_page(const char* language) {
  String lang = language;
  if (lang == "english") {
    // lib_set_text("label", "label1_sub_hal1", "Operating Room");
    lib_set_text("label", "label1_text_waktu_anestesi", "ANESTHESIA TIME");
    lib_set_text("label", "label1_text_waktu_operasi", "OPERATING TIME");
    lib_set_text("label", "label1_gas_medik", "MEDICAL GAS PRESSURE STATUS");
    lib_set_text("label", "label_ambient", "ROOM AMBIENT");
    lib_set_text("label", "label1_temperatur", "TEMPERATURE (˚C)");
    lib_set_text("label", "label1_kelembapan", "HUMIDITY (%)");
    lib_set_text("label", "label_tittle_tekanan", "PRESSURE (kPa)");
    lib_set_text("label", "label1_gas_udara", "AIR");
    lib_set_text("label", "label1_vacuum", "VACUUM");
    lib_set_text("label", "label_timeoutWait", "PLEASE WAIT ...");
  } else {
    // lib_set_text("label", "label1_sub_hal1", "Ruang Operasi");
    lib_set_text("label", "label1_text_waktu_anestesi", "WAKTU ANASTESI");
    lib_set_text("label", "label1_text_waktu_operasi", "WAKTU OPERASI");
    lib_set_text("label", "label1_gas_medik", "STATUS TEKANAN GAS MEDIS");
    lib_set_text("label", "label_ambient", "AMBIENT RUANGAN");
    lib_set_text("label", "label1_temperatur", "SUHU (˚C)");
    lib_set_text("label", "label1_kelembapan", "KELEMBAPAN (%)");
    lib_set_text("label", "label_tittle_tekanan", "TEKANAN (kPa)");
    lib_set_text("label", "label1_gas_udara", "UDARA");
    lib_set_text("label", "label1_vacuum", "VAKUM");
    lib_set_text("label", "label_timeoutWait", "SILAHKAN TUNGGU ...");
  }
}
void update_setting_page(const char* language) {
  String lang = language;
  if (lang == "english") {
    lib_set_text("label", "label_atur_bahasa", "Language");
    lib_set_text("label", "labelctrl_kecerahan_layar", "Display Brightness");
    lib_set_text("label", "label1_atur_tanggal_waktu", "Date and Time Setting");
    lib_set_text("label", "labelset_atur_volume", "Volume Setting");
    lib_set_text("label", "labelset_nama_ruangan", "Room");
    lib_set_text("button", "butt_Jsav", "Save");
    lib_set_text("button", "butt_g_sv", "Save");
    lib_set_text("button", "butt_Gsav", "Save");
  } else {
    lib_set_text("label", "label_atur_bahasa", "Bahasa");
    lib_set_text("label", "labelctrl_kecerahan_layar", "Kecerahan Layar");
    lib_set_text("label", "label1_atur_tanggal_waktu", "Atur Tanggal dan Waktu");
    lib_set_text("label", "labelset_atur_volume", "Atur Suara");
    lib_set_text("label", "labelset_nama_ruangan", "Nama Ruangan");
    lib_set_text("button", "butt_Jsav", "Simpan");
    lib_set_text("button", "butt_g_sv", "Simpan");
    lib_set_text("button", "butt_Gsav", "Simpan");
  }
}
void update_control_page(const char* language) {
  String lang = language;
  if (lang == "english") {
    lib_set_text("label", "label_min_pressr_n2o", "Min N2O Pressure");
    lib_set_text("label", "label_max_pressr_n2o", "Max N2O Pressure");
    lib_set_text("label", "label_min_pressr_o2", "Min O2 Pressure");
    lib_set_text("label", "label_max_O2", "Max O2 Pressure");
    lib_set_text("label", "Udaraa", "Air (BAR)");
    lib_set_text("label", "Vakum", "Vacuum (mmHg)");
    lib_set_text("label", "label_min_udaraa", "Min Air Pressure");
    lib_set_text("label", "label1_max_udaara", "Max Air Pressure");
    delay(10);
    lib_set_text("label", "label1_min_vakum", "Min Vacuum Pressure");
    lib_set_text("label", "label1_max_vakum", "Max Vacuum Pressure");
    lib_set_text("label", "Suhu", "Temperature (˚C)");
    lib_set_text("label", "label1_max_suhu", "Max Temperature");
    lib_set_text("label", "label1_min_suhu", "Min Temperature");
    lib_set_text("label", "Kelembapan", "Humidity (%)");
    lib_set_text("label", "label_max_kelembapan", "Max Humidity");
    lib_set_text("label", "label1_min_kelembapan_copy1", "Min Humidity");
    lib_set_text("label", "labelKodeKeamanan", "Security Code");

    lib_set_text("label", "label1_lampu1_", "Light 1");
    lib_set_text("label", "label1_lampu2_", "Light 2");
    lib_set_text("label", "label_lampu3", "Light 3");
    lib_set_text("label", "label_lampu4", "Light 4");
    lib_set_text("label", "label_lampu5", "Light 5");

  } else {
    lib_set_text("label", "label_min_pressr_n2o", "Min Tekanan N2O");
    lib_set_text("label", "label_max_pressr_n2o", "Max Tekanan N2O");
    lib_set_text("label", "label_min_pressr_o2", "Min Tekanan O2");
    lib_set_text("label", "label_max_O2", "Max Tekanan O2");
    lib_set_text("label", "Udaraa", "Udara (BAR)");
    lib_set_text("label", "Vakum", "Vakum (mmHg)");
    lib_set_text("label", "label_min_udaraa", "Min Tekanan Udara");
    lib_set_text("label", "label1_max_udaara", "Max Tekanan Udara");
    delay(10);
    lib_set_text("label", "label1_min_vakum", "Min Tekanan Vakum");
    lib_set_text("label", "label1_max_vakum", "Max Tekanan Vakum");
    lib_set_text("label", "Suhu", "Suhu (˚C)");
    lib_set_text("label", "label1_max_suhu", "Max Suhu");
    lib_set_text("label", "label1_min_suhu", "Min Suhu");
    lib_set_text("label", "Kelembapan", "Kelembapan (%)");
    lib_set_text("label", "label_max_kelembapan", "Max Kelembapan");
    lib_set_text("label", "label1_min_kelembapan_copy1", "Min Kelembapan");
    lib_set_text("label", "labelKodeKeamanan", "Kode Keamanan");

    lib_set_text("label", "label1_lampu1_", "Lampu 1");
    lib_set_text("label", "label1_lampu2_", "Lampu 2");
    lib_set_text("label", "label_lampu3", "Lampu 3");
    lib_set_text("label", "label_lampu4", "Lampu 4");
    lib_set_text("label", "label_lampu5", "Lampu 5");
  }
}

void update_anastesi_pop_up(const char* language) {
  String lang = language;
  if (lang == "english") {
    lib_set_text("label", "label_bg_settinganes", "    Set Anaesthesia Time");
    lib_set_text("label", "label_jam_anestesi", "Hours");
    lib_set_text("label", "label_menit_anestesi", "Minutes");
    lib_set_text("label", "label_detik_anestesi", "Seconds");
    lib_set_text("button", "butt_Gsav", "Save");
  } else {
    lib_set_text("label", "label_bg_settinganes", "    Atur Waktu Anastesi");
    lib_set_text("label", "label_jam_anestesi", "Jam");
    lib_set_text("label", "label_menit_anestesi", "Menit");
    lib_set_text("label", "label_detik_anestesi", "Detik");
    lib_set_text("button", "butt_Gsav", "Simpan");
  }
}

void update_details_popup(const char* language) {
  String lang = language;
  if (lang == "english") lib_set_text("label", "label_INFO", "    Details");
  else lib_set_text("label", "label_INFO", "    Info");
}

void update_password_popup(const char* language) {
  String lang = language;
  if (lang == "english") {
    lib_set_text("label", "labelKodeKeamanan", "Security Code");
    lib_set_text("button", "button_Bataal", "Cancel");
    lib_set_text("edit", "edit_kode", "Enter Security Code");
    lib_set_text("label", "labelverif", "Incorrect Code!");
  } else {
    lib_set_text("label", "labelKodeKeamanan", "Kode Keamanan");
    lib_set_text("button", "button_Bataal", "Batal");
    lib_set_text("edit", "edit_kode", "Masukkan Kode Keamanan");
    lib_set_text("label", "labelverif", "Kode Salah!");
  }
}

void update_kalibrasi_page(const char* language) {
  String lang = language;
  if (lang == "english") {
    lib_set_text("label", "label1_sub_halaman_control_copy1", "Calibration");
    lib_set_text("label", "label_k_N2O", "N2O Pressure");
    lib_set_text("label", "label_k_O2", "O2 Pressure");
    lib_set_text("label", "label_k_Vakum", "Vacuum Pressure");
    lib_set_text("label", "label_k_air", "Air Pressure");
    lib_set_text("label", "label_k_Humidity", "Humidity");
    lib_set_text("label", "label_k_suhu", "Temperature");
    lib_set_text("button", "butt_k_N2O", "Calibrate");
    lib_set_text("button", "butt_k_O2", "Calibrate");
    lib_set_text("button", "butt_k_vakum", "Calibrate");
    lib_set_text("button", "butt_k_air", "Calibrate");
    lib_set_text("button", "butt_k_Humidity", "Calibrate");
    lib_set_text("button", "butt_k_suhu", "Calibrate");
  } else {
    lib_set_text("label", "label1_sub_halaman_control_copy1", "Kalibrasi");
    lib_set_text("label", "label_k_N2O", "Tekanan N20");
    lib_set_text("label", "label_k_O2", "Tekanan O2");
    lib_set_text("label", "label_k_Vakum", "Tekanan Vakum");
    lib_set_text("label", "label_k_air", "Tekanan Udara");
    lib_set_text("label", "label_k_Humidity", "Kelembapan");
    lib_set_text("label", "label_k_suhu", "Suhu");
    lib_set_text("button", "butt_k_N2O", "Kalibrasi");
    lib_set_text("button", "butt_k_O2", "Kalibrasi");
    lib_set_text("button", "butt_k_vakum", "Kalibrasi");
    lib_set_text("button", "butt_k_air", "Kalibrasi");
    lib_set_text("button", "butt_k_Humidity", "Kalibrasi");
    lib_set_text("button", "butt_k_suhu", "Kalibrasi");
  }
}

void update_kalibrasi_popup(const char* language) {
  String lang = language;
  int ids = dps.getSensorNumber();
  if (lang == "english") {

    lib_set_text("label", "label_judul", "    Calibration");

    // lib_set_text("label", "label2_copy1","Calibration Instructions");
    lib_set_text("label", "label_baris1_copy1", "1. There are choices of 4, 6 and 11 points of data samples that can be");
    lib_set_text("label", "label_baris2_copy1", "used to perform calibration.");
    lib_set_text("label", "label_baris5_copy1", "3. Apply a force to the sensor according to the displayed reference value,");
    lib_set_text("label", "label_baris6_copy1", "then enter the measured value on the calibrator to the screen.");
    lib_set_text("label", "label_baris7_copy1", "4. The sensor value will be displayed automatically according to");
    lib_set_text("label", "label_baris7_5_copy1", "the current reading.");
    lib_set_text("label", "label_baris8_copy1", "5. Press the next button to save and continue to the next reference.");
    lib_set_text("label", "label_baris9_copy1", "6. If all the data has been filled in, a data report will be appeared.");
    lib_set_text("label", "label_baris10_copy1", "7. If the data is confirmed to be correct, press the save button to save");
    lib_set_text("label", "label_baris11_copy1", "the calibration data.");

    lib_set_text("button", "button_k_next_copy1", "Next");
    lib_set_text("button", "button_k_resetKalibrasi", "Reset");
    lib_set_text("label", "label_pembacaan", "Sensor Readings");
    lib_set_text("label", "label_k_errorInput", "Should be close to reference value");
    lib_set_text("button", "button_k_next", "Next");
    lib_set_text("label", "label_referensi1", "Reference");
    lib_set_text("label", "label_referensi1_copy1", "Reference");
    lib_set_text("label", "label_referensi1_copy2", "Reference");
    lib_set_text("button", "button_k_kalibrasi", "Save");
    lib_set_text("button", "button_k_kalibrasi_copy1", "Save");
    lib_set_text("button", "button_k_kalibrasi_copy2", "Save");
    lib_set_text("label", "label1", "Amount of Data Points Used");
    lib_set_text("button", "button_k_4sample", "4 Data Samples");
    lib_set_text("button", "button_k_6sample", "6 Data Samples");
    lib_set_text("button", "button_k_11sample", "11 Data Samples");
    lib_set_text("label", "label2", "Calibration Data Saved Successfully");
    lib_set_text("button", "button_k_tutup", "Close");
    lib_set_text("button", "button_k_batal", "Cancel");
    lib_set_text("button", "button_k_okReset", "Reset");
    lib_set_text("label", "label_k_resetKalibrasi_copy1", "Calibration Data Reset Successfully");
    lib_set_text("button", "button_k_tutup_copy1", "Close");
  } else {
    lib_set_text("label", "label_judul", "    Kalibrasi");
    lib_set_text("label", "label_baris1_copy1", "1. Terdapat pilihan 4, 6 dan 11 jumlah titik sample yang dapat");
    lib_set_text("label", "label_baris2_copy1", "digunakan untuk melakukan kalibrasi.");
    lib_set_text("label", "label_baris5_copy1", "3. Beri input pada sensor sesuai range nilai referensi yang ");
    lib_set_text("label", "label_baris6_copy1", "ditentukan, lalu masukkan nilai yang terukur pada kalibrator.");
    lib_set_text("label", "label_baris7_copy1", "4. Nilai pembacaan sensor akan otomatis ditampilkan sesuai");
    lib_set_text("label", "label_baris7_5_copy1", "dengan pembacaan saat ini.");
    lib_set_text("label", "label_baris8_copy1", "5. Tekan tombol Lanjut untuk menyimpan dan melanjutkan ke referensi selanjutnya.");
    lib_set_text("label", "label_baris9_copy1", "6. Jika seluruh data telah diisi, maka akan muncul report data yang telah diinput.");
    lib_set_text("label", "label_baris10_copy1", "7. Jika data sudah dipastikan benar, tekan tombol simpan untuk menyimpan data ");
    lib_set_text("label", "label_baris11_copy1", "Kalibrasi pada alat.");

    lib_set_text("button", "button_k_next_copy1", "Lanjut");
    lib_set_text("button", "button_k_resetKalibrasi", "Reset");
    lib_set_text("label", "label_pembacaan", "Pembacaan Sensor");
    lib_set_text("label", "label_k_errorInput", "Harus mendekati nilai referensi");
    lib_set_text("button", "button_k_next", "Lanjut");
    lib_set_text("label", "label_referensi1", "Referensi");
    lib_set_text("label", "label_referensi1_copy1", "Referensi");
    lib_set_text("label", "label_referensi1_copy2", "Referensi");
    lib_set_text("button", "button_k_kalibrasi", "Simpan");
    lib_set_text("button", "button_k_kalibrasi_copy1", "Simpan");
    lib_set_text("button", "button_k_kalibrasi_copy2", "Simpan");
    lib_set_text("label", "label1", "Jumlah titik yang digunakan:");
    lib_set_text("button", "button_k_4sample", "4 Sample Data");
    lib_set_text("button", "button_k_6sample", "6 Sample Data");
    lib_set_text("button", "button_k_11sample", "11 Sample Data");
    lib_set_text("label", "label2", "Data Kalibrasi Berhasil Disimpan");
    lib_set_text("button", "button_k_tutup", "Tutup");
    lib_set_text("button", "button_k_batal", "Batal");
    lib_set_text("button", "button_k_okReset", "Reset");
    lib_set_text("label", "label_k_resetKalibrasi_copy1", "Data Kalibrasi Berhasil Direset");
    lib_set_text("button", "button_k_tutup_copy1", "Tutup");
  }
  if (ids == 0 || ids == 1 || ids == 2) {
    if (lang == "english") {
      lib_set_text("label", "label2_copy1", "Pressure Sensor Calibration Instruction:");
      lib_set_text("label", "label_baris3_copy1", "2. For 4 sample points, the data range is from 1 to 10 Bar. For 6 and 11");
      lib_set_text("label", "label_baris4_copy1", "sample points, the data range is from 1 to 11 Bar.");
    } else {
      lib_set_text("label", "label2_copy1", "Petunjuk Kalibrasi Sensor Tekanan:");
      lib_set_text("label", "label_baris3_copy1", "2. Untuk 4 titik sample, range data ada pada 1 hingga 10 Bar. Untuk 6 dan 11");
      lib_set_text("label", "label_baris4_copy1", "titik sample, range data pada 1 hingga 11 Bar.");
    }
  } else if (ids == 3) {
    if (lang == "english") {
      lib_set_text("label", "label2_copy1", "Vacuum Sensor Calibration Instruction:");
      lib_set_text("label", "label_baris3_copy1", "2. For 4 sample points, the data range is from -675 to 0 mmHg. For 6 and 11");
      lib_set_text("label", "label_baris4_copy1", "sample points, the data range is from -750 to 0 mmHg.");
    } else {
      lib_set_text("label", "label2_copy1", "Petunjuk Kalibrasi Sensor Vakum:");
      lib_set_text("label", "label_baris3_copy1", "2. Untuk 4 titik sample, range data ada pada -675 hingga 0 mmHg. Untuk 6 dan 11");
      lib_set_text("label", "label_baris4_copy1", "titik sample, range data pada -750 hingga 0 mmHg.");
    }
  } else if (ids == 4) {
    if (lang == "english") {
      lib_set_text("label", "label2_copy1", "Temperature Sensor Calibration Instruction:");
      lib_set_text("label", "label_baris3_copy1", "2. For 4 sample points, the data range is from 16 to 25 °C. For 6 and 11");
      lib_set_text("label", "label_baris4_copy1", " sample points, the data range is from 16 to 26 °C.");
    } else {
      lib_set_text("label", "label2_copy1", "Petunjuk Kalibrasi Sensor Suhu:");
      lib_set_text("label", "label_baris3_copy1", "2. Untuk 4 titik sample, range data ada pada 16 hingga 25 °C. Untuk 6 dan 11");
      lib_set_text("label", "label_baris4_copy1", "titik sample, range data pada 16 hingga 26 °C.");
    }
  } else if (ids == 5) {
    if (lang == "english") {
      lib_set_text("label", "label2_copy1", "Humidity Sensor Calibration Instruction:");
      lib_set_text("label", "label_baris3_copy1", "2. For 4 sample points, the data range is from 30 to 66 %. And for 6 and 11");
      lib_set_text("label", "label_baris4_copy1", "sample points, the data range is from 30 to 70 %.");
    } else {
      lib_set_text("label", "label2_copy1", "Petunjuk Kalibrasi Sensor Kelembapan:");
      lib_set_text("label", "label_baris3_copy1", "2. Untuk 4 titik sample, range data ada pada 30 hingga 66 % . Dan untuk 6 dan 11");
      lib_set_text("label", "label_baris4_copy1", "titik sample, range data pada 30 hingga 70 %.");
    }
  }
}

void set_button_startstop(const char* condition) {
  if (condition == "start") {  //tombol start enable, tombol stop disable
    lib_set_enaVisi("butt_d_str", 1);
    lib_set_enaVisi("butt_d_stp", 0);
  } else if (condition == "stop") {  //tombol start disable, tombol stop enable
    lib_set_enaVisi("butt_d_str", 0);
    lib_set_enaVisi("butt_d_stp", 1);
  }
}

//halaman voip
void update_voip_page(const char* language) {
  String lang = language;
  if (lang == "english") {
    lib_set_text("button", "buttonKeypad", "Keypad");
    lib_set_text("button", "buttonAddrs", "Contacts");
    lib_set_text("label", "label25", "Delete Contact?");
    lib_set_text("button", "button_dlt_s", "Delete");
    lib_set_text("button", "button_ccl_s", "Cancel");
    lib_set_text("label", "label26", "Name");
    lib_set_text("button", "button10", "Save");
    lib_set_text("button", "button10_copy1", "Cancel");
    lib_set_text("label", "label27_copy1", "Delete All Saved Contacts?");
    lib_set_text("button", "button_y_dltAll", "Delete");
    lib_set_text("button", "button_n_dltAll", "Cancel");
    lib_set_text("label", "label_nocontact", "No Contact Saved");
    lib_set_text("label", "label18", "    VoIP Phone");
    lib_set_text("label", "label20", "    VoIP Configuration");
    lib_set_text("label", "label23", "Connection Status");
    lib_set_text("label", "lababel_v_contactFull", "Contact Full!");
    lib_set_text("button", "button_v_saveSetting", "Save");
    lib_set_text("label", "label20", "    VoIP Configuration");
  } else {
    lib_set_text("button", "buttonKeypad", "Keypad");
    lib_set_text("button", "buttonAddrs", "Kontak");
    lib_set_text("label", "label25", "Hapus Kontak");
    lib_set_text("button", "button_dlt_s", "Hapus");
    lib_set_text("button", "button_ccl_s", "Batal");
    lib_set_text("label", "label26", "Nama");
    lib_set_text("button", "button10", "Simpan");
    lib_set_text("button", "button10_copy1", "Batal");
    lib_set_text("label", "label27_copy1", "Hapus Semua Kontak Yang Tersimpan??");
    lib_set_text("button", "button_y_dltAll", "Hapus");
    lib_set_text("button", "button_n_dltAll", "Batal");
    lib_set_text("label", "label_nocontact", "Tidak Ada Kontak Yang Disimpan");
    lib_set_text("label", "label18", "    Telepon VoIP");
    lib_set_text("label", "label20", "    Konfigurasi VoIP");
    lib_set_text("label", "label23", "Status Koneksi");
    lib_set_text("label", "lababel_v_contactFull", "Kontak Penuh!");
    lib_set_text("button", "button_v_saveSetting", "Simpan");
    lib_set_text("label", "label20", "    Konfigurasi VoIP");
    lib_set_text("button", "button10", "Simpan");
    lib_set_text("button", "button10_copy1", "Batal");
  }
}
