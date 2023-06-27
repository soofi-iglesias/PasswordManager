# Password Manager
### Trabajo Práctico - Informática 2023

Una contraseña segura debe estar formada por mayúsculas, minúsculas, números y caracteres especiales, y tener más de ocho caracteres. Tampoco debe ser fácil de adivinar, ni debe estar compuesta por la unión de una palabra o nombre y una fecha. Y, siendo sinceros, cumplir con todos estos requisitos se hace especialmente complicado recordar todas nuestras contraseñas.

Entonces, nosotras nos propusimos un proyecto (mejor dicho, un desafío) con el objetivo de diseñar y programar un **Gestor de Contraseñas** en lenguaje C, que incluya todos los conocimientos adquiridos durante la materia Informática.
Creamos un sistema en el que una persona es capaz de **ingresar, modificar, mostrar y guardar sus contraseñas**. Además, es posible crear distintos **perfiles independientes**, que permite que más de un usuario pueda guardar sus contraseñas con eficacia y seguridad.



Entre sus funciones, se encuentran:
  - Acceder ingresando a tu perfil, con unacontraseña maestra. Sí, como una llave maestra.
  - Ingresar nueva contraseña: el usuario introduce una contraseña y junto con un ID.
    Ejemplo: el usuario quiere ingresar la contraseña de su cuenta de Instagram.
    		ID: usuario_56
    		Contraseña: estaEsMiContraseña56$
  - Buscar y mostrar contraseña: el usuario introduce el ID y se muestra en pantalla ID y contraseña.
  - Mostrar todas las contraseñas: en formato de lista, se muestran las contraseñas junto con su respectivo ID.
  - Cambiar contraseña: el usuario introduce el ID y se le permite ingresar una nueva contraseña.
  - Eliminar contraseña: el usuario introduce el ID y se le permite ingresar una nueva contraseña.
  - Guardar contraseñas en un archivo.

Para una futura versión del programa se podrían incluir ciertas mejoras, tales como agregar un campo en la estructura password para que se tenga la capacidad de **filtrar o clasificar** las contraseñas por categorías asignadas por el usuario. Esto permitiría que se puedan exponer las contraseñas según su clasificación en caso de necesitarlo u olvidarse el keyword.

También, se le podría agregar una opción de sugerencia de contraseña segura, que cumpla con todos los requisitos para ser, justamente, segura. Teniendo en cuenta que si alguien más además del usuario accede a está información personal, podría resultar sumamente grave.

Otra posible forma de mejorar sería implementar un restablecimiento de la contraseña asociada a un perfil, ya que en el caso de olvido o extravío no se pierda toda la información registrada previamente. Sin embargo, esta funcionalidad requeriría más conocimientos que los aprendidos en el transcurso de esta materia y mucho tiempo de búsquedas en Google sobre el tema. Probablemente, incluiría algún tipo de base de datos en internet. Y habría que encontrar la manera de relacionar esa base de datos con una aplicación de consola. Problema para las futuras Hina y Sofi.

Por último, para evitar que sus contraseñas se vean vulneradas ante un hackeo y que sean modificadas de forma externa, sería interesante agregar un sistema de encriptado a todos los archivos que se manejan.
