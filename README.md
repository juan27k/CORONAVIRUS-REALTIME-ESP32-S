# j27k2020
Coronavirus - Arduino - LCD 16X2 - Info RealTime
Es un proyecto que utiliza el modulo ESP 32-S de arduino para proporcionar 
datos actualizados sobre el brote de coronavirus
Incluye números sobre casos confirmados, y muertes.
El programa cliente de arduino se conecta a una web service API con la siguiente URL:
https://coronavirus-tracker-api.herokuapp.com/v2/locations
# Fuentes de datos disponibles:
Actualmente hay 2 fuentes de datos diferentes disponibles para recuperar los datos:
jhu - https://github.com/CSSEGISandData/COVID-19 - Repositorio mundial de datos operado por el Centro de Ciencias e Ingeniería de Sistemas de la Universidad Johns Hopkins (JHU CSSE).
csbs : https://www.csbs.org/information-covid-19-coronavirus : datos del condado de EE. UU. que provienen de la Conferencia de supervisores de bancos estatales.
La fuente de datos jhu se usará como fuente predeterminada si no especifica un parámetro fuente en su solicitud.
# Sitio y referencias de mas informacion acerca de la API:
https://github.com/ExpDev07/coronavirus-tracker-api#available-data-sources
![lcd2](https://user-images.githubusercontent.com/16866881/77587963-af7d6780-6ec7-11ea-8f43-cbb25ca9df1c.jpeg)
# Autor
jmXoft - juan Manuel Cichello

