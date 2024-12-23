import { useState, useRef, useEffect } from "react";
import Button from "./Button";

function ErrorMessage() {
	return (
		<p className="text-center z-50 bg-black rounded py-1 px-2 text-white">
			Cannot load video feed. Check address and robot status.
		</p>
	);
}

function Image({ videoRef, src, setError }) {
	return (
		<img
			ref={videoRef}
			id="video"
			src={`http://${src}/video_feed`}
			alt="video"
			onError={() => setError(true)}
			onLoad={() => setError(false)}
		/>
	);
}

export default function Video() {
	const [src, setSrc] = useState(false);
	const [error, setError] = useState(false);

	const videoRef = useRef();

	useEffect(() => {
		setError(false);

		if (videoRef.current) {
			videoRef.current.src = videoRef.current.src;
		}
	}, [videoRef]);

	function handleChangeAddress(e) {
		e.preventDefault();
		console.log("change address");

		setError(false);
		setSrc(e.target[0].value);
	}

	return (
		<div className="flex flex-col gap-2 border border-primary-500 rounded p-2">
			{error ? (
				<ErrorMessage />
			) : (
				<Image videoRef={videoRef} src={src} setError={setError} />
			)}

			<form className="grid grid-cols-2 gap-2" onSubmit={handleChangeAddress}>
				<div className="flex flex-col gap-2 relative">
					<input
						placeholder="[ip]:[port]"
						pattern="^(localhost|\d{1,3}(\.\d{1,3}){3}):(\d{1,5})$"
						className="rounded p-2 border border-gray-500 invalid:bg-red-100 peer"
					/>
					<label
						htmlFor="video"
						className="absolute transition text-white -bottom-1 left-2 bg-black rounded py-1 px-2 translate-y-full peer-invalid:opacity-100 opacity-0"
					>
						Input address must follow the format [ip]:[port]
					</label>
				</div>

				<Button
					type="submit"
					primary
					className="bg-blue-500 text-white rounded p-2"
				>
					Connect
				</Button>
			</form>
		</div>
	);
}
